#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PositionComponent.h"

#include "Player.h"
#include "Bullet.h"
#include "Map.h"

Player::Player() :
	State_(this),
	//AnimationState_(this),
	KeyState_Update_(true),
	ColState_Update_(true),
	State_Update_(true),
	KeyState_Up_(false),
	KeyState_Down_(false),
	KeyState_Left_(false),
	KeyState_Right_(false),
	KeyState_RockOn_(false),
	KeyState_Shoot_(false),
	KeyState_Bomb(false),
	KeyState_Jump_(false),
	KeyState_Hit_(false),
	KeyState_Dash_(false),
	ColState_Ground(false),
	ColState_Hit_(false),
	HitInvince_(false),
	HitInvinceTime_(0.f),
	Camera_(nullptr),
	BulletPoint_(nullptr),
	PlayerHitBox(nullptr),
	PlayerMovingCollision(nullptr),
	PlayerCollision(nullptr),
	PlayerImageRenderer(nullptr),
	BulletType_(BulletType::Default),
	ShootingDir_(),
	Dir_(AnimationDirection::Right),
	TimeCheck_(0.f),
	ShootingInterTime_(0.f),
	DistTimeCheck_(0.f),
	GravitySpeed_(0.f),
	GravityAcc_(2.f),
	PrevAniSize_{}
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

	BulletInfo_.BulletSpeed_ = 0.f;

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

StateInfo Player::ChangeState()
{
	if (true == ColState_Hit_)
	{
		State_.ChangeState("Hit");
		return "Hit";
	}
	else if (true == KeyState_Bomb)
	{
		State_.ChangeState("Bomb");
		return "Bomb";
	}
	else if (true == KeyState_Jump_)
	{
		State_.ChangeState("Jump");
		return "Jump";
	}
	else if (true == KeyState_Dash_)
	{
		State_.ChangeState("Dash");
		return "Dash";
	}
	else if (true == KeyState_RockOn_)
	{
		State_.ChangeState("RockOn");
		return "RockOn";
	}
	else if (true == KeyState_Down_)
	{
		State_.ChangeState("Duck");
		return "Duck";
	}
	else if (true == KeyState_Right_ || true == KeyState_Left_)
	{
		State_.ChangeState("Walk");
		return "Walk";
	}
}

const std::string Player::CheckState()
{
	if (true == ColState_Hit_)
	{
		CurState_ = "Hit";
	}
	else if (true == KeyState_Bomb)
	{
		CurState_ = "Bomb";
	}
	else if (true == KeyState_Jump_)
	{
		CurState_ = "Jump";
	}
	else if (true == KeyState_Dash_)
	{
		CurState_ = "Dash";
	}
	else if (true == KeyState_RockOn_)
	{
		CurState_ = "RockOn";
	}
	else if (true == KeyState_Down_)
	{
		CurState_ = "Duck";
	}
	else if (true == KeyState_Right_ || true == KeyState_Left_)
	{
		CurState_ = "Walk";
	}
	else
	{
		CurState_ = "Idle";
	}

	return CurState_;
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
		//if (Dir_ == AnimationDirection::Left)
		//{
		//	BulletPoint_->GetTransform()->SetLocalPosition(float4 { -50.f, -50.f, static_cast<int>(ZOrder::Z00Fx00) });

		//	float degree = atanf(BulletInfo_.MoveDir_.y / -BulletInfo_.MoveDir_.x);
		//	degree *= GameEngineMath::RadianToDegree;

		//	BulletPointOrigin_->GetTransform()->SetLocalRotation(float4{ 0.f,0.f,degree });
		//}
		//else
		//{
		//	BulletPoint_->GetTransform()->SetLocalPosition(float4{ 50.f, -50.f, static_cast<int>(ZOrder::Z00Fx00) });

		//	float degree = atanf(BulletInfo_.MoveDir_.y / BulletInfo_.MoveDir_.x);
		//	degree *= GameEngineMath::RadianToDegree;

		//	BulletPointOrigin_->GetTransform()->SetLocalRotation(float4{ 0.f,0.f,degree });
		//}

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
	//if (_BulletInfo.MoveDir_.x < 0)
	//{
	//	Bullet->GetTransform()->SetHorizenInvertTransform();
	//}
	
	
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

//
//const bool Player::MapCollisionMove(float4 _MoveDist, float _DeltaTime)
//{
//	Move(_MoveDist, _DeltaTime);
//	
//	float4 Color = Map::GetColor(GetTransform());
//
//	if (Color == float4::BLACK)
//	{
//		Move(0.f,10.f,1.f);
//		Color = Map::GetColor(GetTransform());
//
//		if (Color == float4::BLACK)
//		{
//			Move(0.f, -10.f, 1.f);
//			Move(-_MoveDist, _DeltaTime);
//
//			return false;
//		}
//
//		else
//		{
//			return true;
//		}
//	}
//
//	return true;
//}
//
//const bool Player::MapCollisionMove(float DirX, float DirY, float _DeltaTime)
//{
//	Move(DirX, DirY,_DeltaTime);
//
//	float4 Color = Map::GetColor(GetTransform());
//
//	if (Color == float4::BLACK)
//	{
//		Move(0.f, 10.f, 1.f);
//		Color = Map::GetColor(GetTransform());
//
//		if (Color == float4::BLACK)
//		{
//			Move(0.f, -10.f, 1.f);
//			Move(-DirX, -DirY, _DeltaTime);
//
//			return false;
//		}
//
//		else
//		{
//			return true;
//		}
//	}
//
//	return true;
//}




