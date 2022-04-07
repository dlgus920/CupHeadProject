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
	, HitInvinceTime_(0.f)
	, Camera_(nullptr)
	, BulletPoint_(nullptr)
	, BulletPointOrigin_(nullptr)
	, PlayerHitBox(nullptr)
	, PlayerMovingCollision(nullptr)
	, PlayerCollision(nullptr)
	, PlayerImageRenderer(nullptr)
	, BulletType_(BulletType::Default)
	, ShootingDir_()
	, Dir_(AnimationDirection::Right)
	, TimeCheck_(0.f)
	, ShootingInterTime_(0.f)
	, DistTimeCheck_(0.f)
	, GravitySpeed_(0.f)
	, GravityAcc_(2.f)
	, PrevAniSize_{}
{
}

Player::~Player()
{
}


void Player::Start()
{
	ComponentSetting();
	AnimationSetting();
	PlayerImageRenderer->SetChangeAnimation("Cup-Idle");

	PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetImageSize());
	PlayerCollision->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetImageSize());
	PlayerHitBox->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetImageSize());

	KeySetting();
	StateSetting();

	Dir_ = AnimationDirection::Right;

	BulletInfo_.BulletSpeed_ = 600.f;

	ChangeShootFunc(&Player::ShootDefalutBullet);

	State_.ChangeState("Idle");
	//ShootingPos_[static_cast<int>(ShootingDir::Right)] =		float4{ 50.f,-50.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Right_Up)] =		float4{ 0.f,0.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Right_Down)] =	float4{ 0.f,0.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Left)] =			float4{ -50.f,-50.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Left_Up)] =		float4{ 0.f,0.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Left_Down)] =	float4{ 0.f,0.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Up_Left)] =		float4{ 0.f,0.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Up_Right)] =		float4{ 0.f,0.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Down_Left)] =	float4{ 0.f,0.f,0.f };
	//ShootingPos_[static_cast<int>(ShootingDir::Down_Right)] =	float4{ 0.f,0.f,0.f };
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
	if (true == ColState_Parry_)
	{
		return "Parry";
	}
	if (true == ColState_Hit_)
	{
		return "Hit";
	}
	else if (true == KeyState_Bomb)
	{
		return "Bomb";
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
	{
		float degree = float4::DegreeDot3DToACosAngle(float4::RIGHT, BulletInfo_.MoveDir_);
		if (BulletInfo_.MoveDir_.y < 0.f)
		{
			degree *= -1.f;
		}

		BulletPointOrigin_->GetTransform()->SetLocalRotation(float4{ 0.f,0.f,degree });
	}

	Bullet_Defalut* Bullet = GetLevel()->CreateActor<Bullet_Defalut>();

	float4 pos = BulletPoint_->GetTransform()->GetWorldPosition();
	pos.z = static_cast<int>(ZOrder::Z00Bullet01);

	Bullet->GetTransform()->SetWorldPosition(pos);
	Bullet->SetBulletInfo(BulletInfo_);

	Image* Birth = GetLevel()->CreateActor<Image>();
	Birth->ImageCreateAnimation("Bullet_Default_Birth.png", "Birth", 0, 3, 0.1, false);
	Birth->SetReserveDeath("Birth");
	Birth->SetAdjustImzgeSize();
	Birth->GetTransform()->SetWorldPosition(pos);
}

float4 Player::GetBulletPoint()
{
	return BulletPoint_->GetTransform()->GetWorldPosition();
}

void Player::GravityUpdate(float _DeltaTime)
{
	GravitySpeed_ -= GravityAcc_;

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

void Player::CheckShootDir()
{
	if (KeyState_Down_ && !KeyState_Up_)
	{
		if (KeyState_Left_ && !KeyState_Right_)
		{
			Dir_ = AnimationDirection::Left;

			BulletInfo_.MoveDir_ = float4::DOWNLEFT;
		}

		else if (KeyState_Right_ && !KeyState_Left_)
		{
			Dir_ = AnimationDirection::Right;

			BulletInfo_.MoveDir_ = float4::DOWNRIGHT;
		}

		else
			BulletInfo_.MoveDir_ = float4::DOWN;
	}

	else if (KeyState_Up_ && !KeyState_Down_)
	{
		if (KeyState_Left_ && !KeyState_Right_)
		{
			Dir_ = AnimationDirection::Left;

			BulletInfo_.MoveDir_ = float4::UPLEFT;
		}

		else if (KeyState_Right_ && !KeyState_Left_)
		{
			Dir_ = AnimationDirection::Right;

			BulletInfo_.MoveDir_ = float4::UPRIGHT;
		}

		else
			BulletInfo_.MoveDir_ = float4::UP;
	}

	else if (KeyState_Left_ && !KeyState_Right_)
	{
		Dir_ = AnimationDirection::Left;

		BulletInfo_.MoveDir_ = float4::LEFT;
	}

	else if (KeyState_Right_ && !KeyState_Left_)
	{
		Dir_ = AnimationDirection::Right;

		BulletInfo_.MoveDir_ = float4::RIGHT;
	}
}
