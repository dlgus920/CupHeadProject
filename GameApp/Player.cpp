#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PositionComponent.h"

#include "Player.h"
#include "Bullet.h"
#include "Map.h"
#include "Image.h"

Player::Player() 
	: State_(this)
	, KeyState_Update_(true)
	, ColState_Update_(true)
	, State_Update_(true)
	, KeyState_Up_(false)
	, KeyState_Down_(false)
	, KeyState_Left_(false)
	, KeyState_Right_(false)
	, KeyState_RockOn_(false)
	, KeyState_Shoot_(false)
	, KeyState_Bomb(false)
	, KeyState_Jump_(false)
	, KeyState_Hit_(false)
	, KeyState_Dash_(false)
	, ColState_Ground(false)
	, ColState_Hit_(false)
	, ColState_Parry_(false)
	, HitInvince_(false)
	, WalkState_Changed_(false)
	, HitInvinceTime_(0.f)
	, Camera_(nullptr)
	, PlayerHitBox(nullptr)
	, PlayerMovingCollision(nullptr)
	, PlayerCollision(nullptr)
	, PlayerImageRenderer(nullptr)
	, Bottom_Card_(nullptr)
	, Bottom_HP_(nullptr)
	, BulletType_(BulletType::Default)
	, ShootingDir_()
	, Dir_(AnimationDirection::Right)
	, TimeCheck_(0.f)
	, ShootingInterTime_(0.f)
	, DistTimeCheck_(0.f)
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
	//TODO: �ٵ� �̰� Ȥ�� �� �߶��� �ؽ�ó ũ�� �״�� ��������?
	// �ƹ����� �ؽ�ó�� �� ũ�⸦ ������ �ִµ� �����Ű���.
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
	// ��ȯ�� �������� ������, ��ü������ �ֺ� ���� ã�� �˾Ƽ� �̵��ϰ� ����

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
	Birth->ImageCreateAnimation("Bullet_Default_Birth.png", "Birth", 0, 3, 0.05, false);
	Birth->SetReserveDeath("Birth");
	Birth->SetAdjustImzgeSize();
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
