#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "PositionComponent.h"

#include "Player.h"
#include "Bullet.h"
#include "Map.h"
#include "Image.h"

Player::Player() 
	: State_(this)
	, blit_(true)
	, KeyState_Up_(false)
	, KeyState_Down_(false)
	, KeyState_Left_(false)
	, KeyState_Right_(false)
	, KeyState_RockOn_(false)
	, KeyState_Shoot_(false)
	, KeyState_Bomb(false)
	, KeyState_Jump_(false)
	, KeyState_Dash_(false)
	, ColState_Ground(false)
	, ColState_Hit_(false)
	, ColState_Parry_(false)
	, HitInvince_(false)
	, WalkState_Changed_(false)
	, AniState_DashEnd_(false)
	, Camera_(nullptr)
	, PlayerHitBox(nullptr)
	, PlayerMovingCollision(nullptr)
	, PlayerParryCollision(nullptr)
	, PlayerImageRenderer(nullptr)
	, Bottom_Card_(nullptr)
	, Bottom_HP_(nullptr)
	, BulletType_(BulletType::Default)
	, ShootingDir_()
	, Dir_(AnimationDirection::Right)
	, TimeCheck_(0.f)
	, ShootingInterTime_(0.f)
	, DistTimeCheck_(0.f)
	, HitInvinceTimeCheck_(0.f)
	, GravitySpeed_(0.f)
	, PrevAniSize_{}
	, HP(0)
	, ParryCount(0)
{
}

Player::~Player()
{
}

void Player::Start()
{
	ComponentSetting();
	AnimationSetting();
	KeySetting();
	StateSetting();

	DefalutSetting();

}

void Player::ChangeAnimation(std::string _animation)
{
	PlayerImageRenderer->SetChangeAnimation(_animation);
	//PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetCurrentTexture()->GetTextureSize());
	//TODO: 근데 이거 혹시 안 잘라진 텍스처 크기 그대로 가져오나?
	// 아무래도 텍스처가 지 크기를 가지고 있는데 좋을거같다.
}

const std::string Player::CheckState()
{
	//if (true == ColState_Parry_)
	//{
	//	return "Parry";
	//}
	if (true == ColState_Hit_)
	{
		return "Hit";
	}
	else if (true == KeyState_Bomb)
	{
		if (Bottom_Card_->GetCardCount() != 0)
		{
			return "Bomb";
		}
	}
	else if (true == KeyState_Jump_)
	{
		return "Jump";
	}
	else if (true == KeyState_Dash_)
	{
		return "Dash";
	}
	else if (true == KeyState_RockOn_)
	{
		return "RockOn";
	}
	else if (true == KeyState_Down_)
	{
		return "Duck";
	}
	else if (true == KeyState_Right_ || true == KeyState_Left_)
	{
		return "Walk";
	}
	else
	{
		return "Idle";
	}
	return "";
}

void Player::Move(float4 MoveDir, float _DeltaTime)
{
	GetTransform()->SetLocalMove(MoveDir * _DeltaTime);
}

void Player::Move(float DirX, float DirY, float _DeltaTime)
{
	GetTransform()->SetLocalMove(float4(DirX, DirY, 0.f) * _DeltaTime);
}

void Player::ChangeShootFunc(void(Player::* _FrameFunc)())
{
	BulletShootFunc_ = std::bind(_FrameFunc, this);
}

void Player::ShootGuidedBullet()
{
	// 소환된 방향으로 나가되, 자체적으로 주변 적을 찾아 알아서 이동하게 해줌

	Bullet_Guided* Bullet = GetLevel()->CreateActor<Bullet_Guided>();
	Bullet->SetBulletInfo(BulletInfo_);
}
void Player::ShootSpreadBullet()
{
	Bullet_Spread* Bullet = GetLevel()->CreateActor<Bullet_Spread>();
	Bullet->SetBulletInfo(BulletInfo_);
}
void Player::ShootDefalutBullet()
{
	Bullet_Defalut* Bullet = GetLevel()->CreateActor<Bullet_Defalut>();

	float4 Pos = GetShootPos();

	Bullet->GetTransform()->SetWorldPosition(Pos);
	Bullet->SetBulletInfo(BulletInfo_);

	Image* Birth = GetLevel()->CreateActor<Image>();
	Birth->GetTransform()->SetLocalScaling(float4{ 140.f,140.f,1.f });
	Birth->ImageCreateAnimation("Bullet_Default_Birth.png", "Birth", 0, 3, 0.05, false);
	Birth->SetReserveDeath("Birth");
	Birth->GetTransform()->SetWorldPosition(Pos);
}

void Player::GravityUpdate(float _DeltaTime)
{
	if (GravitySpeed_ < -800.f)
	{
		GravitySpeed_ = -800.f;
	}

	Move(float4(0.f, GravitySpeed_, 0.f), _DeltaTime);
}

void Player::GravityClear()
{
	GravitySpeed_ = 0.f;
}

const float4 Player::GetShootPos()
{
	float4 orginPos = GetTransform()->GetWorldPosition();

	const float4 retPos = { ShootingPos_[static_cast<int>(ShootingDir_)].x + orginPos.x,
					ShootingPos_[static_cast<int>(ShootingDir_)].y + orginPos.y,
					ShootingPos_[static_cast<int>(ShootingDir_)].z};

	return retPos;
}

void Player::EffectDust()
{
	GameEngineRandom ran;

	int swit = ran.RandomInt(0, 5);

	GameEngineActor* DustAct = GetLevel()->CreateActor<GameEngineActor>();
	GameEngineImageRenderer* Dust = DustAct->CreateTransformComponent<GameEngineImageRenderer>();

	switch (swit)
	{
	case 0:	
		Dust->CreateAnimation("PlayerDust.png", "PlayerDust", 0, 18, 0.04);
		break;
	case 1:
		Dust->CreateAnimation("PlayerDust.png", "PlayerDust", 20, 39, 0.04);
		break;
	case 2:
		Dust->CreateAnimation("PlayerDust.png", "PlayerDust", 40, 57, 0.04);
		break;
	case 3:
		Dust->CreateAnimation("PlayerDust.png", "PlayerDust", 60, 78, 0.04);
		break;
	case 4:
		Dust->CreateAnimation("PlayerDust.png", "PlayerDust", 80, 99, 0.04);
		break;
	case 5:
		Dust->CreateAnimation("PlayerDust.png", "PlayerDust", 100, 117, 0.04);
		break;
	}

	Dust->SetEndCallBack("PlayerDust", std::bind(&GameEngineActor::Death, DustAct));
	Dust->SetChangeAnimation("PlayerDust");
	Dust->SetAdjustImzgeSize();

	float4 Pos = GetTransform()->GetWorldPosition();
	Pos.y -= 75.f;
	Pos.z += 1.f;
	DustAct->GetTransform()->SetWorldPosition(Pos);
}

void Player::EffectDashDust()
{
	GameEngineActor* DustAct = GetLevel()->CreateActor<GameEngineActor>();
	GameEngineImageRenderer* Dust = DustAct->CreateTransformComponent<GameEngineImageRenderer>(); // 이미지 렌더러 하나를 미리 만들고 돌려쓰는게 나을듯???

	Dust->CreateAnimation("DashDust.png", "DashDust", 0, 12, 0.04);
	Dust->SetEndCallBack("DashDust", std::bind(&GameEngineActor::Death, DustAct));
	Dust->SetChangeAnimation("DashDust");
	Dust->SetAdjustImzgeSize();

	float4 Pos = GetTransform()->GetWorldPosition();
	Pos.y -= 75.f;
	Pos.z += 1.f;
	DustAct->GetTransform()->SetWorldPosition(Pos);
}
void Player::EffectParry()
{
	GameEngineActor* DustAct = GetLevel()->CreateActor<GameEngineActor>();
	GameEngineImageRenderer* Dust = DustAct->CreateTransformComponent<GameEngineImageRenderer>(); // 이미지 렌더러 하나를 미리 만들고 돌려쓰는게 나을듯???

	Dust->CreateAnimation("ParryEffect.png", "ParryEffect", 0, 8, 0.04);
	Dust->SetEndCallBack("ParryEffect", std::bind(&GameEngineActor::Death, DustAct));
	Dust->SetChangeAnimation("ParryEffect");
	Dust->SetAdjustImzgeSize();

	float4 Pos = GetTransform()->GetWorldPosition();
	Pos.y -= 75.f;
	Pos.z += 1.f;
	DustAct->GetTransform()->SetWorldPosition(Pos);
}
void Player::EffectHit() 
{
	GameEngineRandom ran;

	int swit = ran.RandomInt(0, 2);

	GameEngineActor* DustAct = GetLevel()->CreateActor<GameEngineActor>();
	GameEngineImageRenderer* Dust = DustAct->CreateTransformComponent<GameEngineImageRenderer>();

	switch (swit)
	{
	case 0:
		Dust->CreateAnimation("HitEffect.png", "HitEffect", 0, 8, 0.03);
		break;
	case 1:
		Dust->CreateAnimation("HitEffect.png", "HitEffect", 9, 17, 0.03);
		break;
	case 2:
		Dust->CreateAnimation("HitEffect.png", "HitEffect", 18, 26, 0.03);
		break;
	}

	Dust->SetEndCallBack("HitEffect", std::bind(&GameEngineActor::Death, DustAct));
	Dust->SetChangeAnimation("HitEffect");
	Dust->SetAdjustImzgeSize();

	float4 Pos = GetTransform()->GetWorldPosition();
	Pos.y -= 75.f;
	Pos.z += 1.f;
	DustAct->GetTransform()->SetWorldPosition(Pos);
}
void Player::EffectJumpLanding() 
{
	GameEngineActor* DustAct = GetLevel()->CreateActor<GameEngineActor>();
	GameEngineImageRenderer* Dust = DustAct->CreateTransformComponent<GameEngineImageRenderer>(); // 이미지 렌더러 하나를 미리 만들고 돌려쓰는게 나을듯???

	Dust->CreateAnimation("LandDust.png", "LandDust", 0, 5, 0.04);
	Dust->SetChangeAnimation("LandDust");
	Dust->SetAdjustImzgeSize();

	Dust->SetEndCallBack("LandDust", std::bind(&GameEngineActor::Death, DustAct));

	float4 Pos = GetTransform()->GetWorldPosition();
	Pos.y -= 100.f;
	Pos.z += 1.f;
	DustAct->GetTransform()->SetWorldPosition(Pos);
}