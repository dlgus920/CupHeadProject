#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

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
	Dir_(AnimationDirection::Right),
	TimeCheck_(0.f),
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

	PlayerImageRenderer->GetTransform()->SetLocalScaling(float4{280.f,280.f,1.f});

	KeySetting();
	StateSetting();

	Dir_ = AnimationDirection::Right;

	ChangeShootFunc(&Player::ShootDefalutBullet);

	State_.ChangeState("Idle");
}

void Player::ChangeAnimation(std::string _animation)
{
	PlayerImageRenderer->SetChangeAnimation(_animation);
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

void Player::ChangeShootFunc(void(Player::* _FrameFunc)(float4))
{
	BulletShootFunc_ = std::bind(_FrameFunc, this, std::placeholders::_1);
}

void Player::ShootGuidedBullet(float4 _Dir)
{
	// 소환된 방향으로 나가되, 자체적으로 주변 적을 찾아 알아서 이동하게 해줌

	Bullet_Guided* Bullet = GetLevel()->CreateActor<Bullet_Guided>();
	Bullet->SetMoveDir(_Dir);
}
void Player::ShootSpreadBullet(float4 _Dir)
{
	Bullet_Spread* Bullet = GetLevel()->CreateActor<Bullet_Spread>();
	Bullet->SetMoveDir(_Dir);
}
void Player::ShootDefalutBullet(float4 _Dir)
{
	Bullet_Defalut* Bullet = GetLevel()->CreateActor<Bullet_Defalut>();
	float4 pos = GetTransform()->GetWorldPosition();
	Bullet->GetTransform()->SetLocalPosition(float4{ pos.x, pos.y, 0.3f });
	Bullet->SetMoveDir(_Dir);
}

float4 Player::GetBulletPoint()
{
	return BulletPoint_->GetLocalPosition();
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



