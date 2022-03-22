#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Bullet.h"
#include "Map.h"

Player::Player() :
	State_(this),
	AnimationState_(this),
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
	Camera_(nullptr),
	BulletPoint_(nullptr),
	PlayerHitBox(nullptr),
	PlayerMovingCollision(nullptr),
	PlayerCollision(nullptr),
	PlayerImageRenderer(nullptr),
	BulletType_(BulletType::Default),
	KeyDir_(KeyDir::None),
	Dir_(AnimationDirection::Right)
{
}

Player::~Player()
{
}


void Player::Start()
{
	//GetTransform()->SetWorldPosition({ 500.0f, -500.0f });

	//{
	//	GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	//	Renderer->SetRenderingPipeLine("Color");
	//	Renderer->GetTransform()->SetLocalScaling({ 100.0f, 20.0f, 1.0f });
	//	Renderer->GetTransform()->SetLocalPosition({ 0.0f, 80.0f, -20.0f });
	//	Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
	//}

	//{
	//	PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	//	PlayerImageRenderer->SetImage("Char.png");
	//	PlayerImageRenderer->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
	//}

	ComponentSetting();
	AnimationSetting();
	KeySetting();
	StateSetting();

	//SetScale(x *= -1, y, z); 가로 뒤집기
	Dir_ = AnimationDirection::Right;
	PlayerImageRenderer->SetChangeAnimation("Cup-Hit-Air");
	State_.ChangeState("Idle");
}

void Player::Update(float _DeltaTime)
{
	//float4 Color = Map::GetColor(GetTransform());

	//if (Color != float4::BLACK)
	//{
	//	GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 100.0f);
	//}

	GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);

	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	if (true == KeyState_Update_)
	{
		KeyUpdate(_DeltaTime);
	}

	if (true == ColState_Update_)
	{
		CollisonUpdate(); // 컬리젼 업데이트에서 상대방과 충돌 여부를 검사하고, stateupdate에서ㅏ 참고하도록 한다.
	}

	if (true == State_Update_)
	{
		State_.Update(_DeltaTime);
	}

	//StateUpdate(_DeltaTime);
	//GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect);

	//State_Update_는 State_.Update중에 설정함



	if (false == ColState_Ground)
	{
		GravityUpdate(_DeltaTime);
	}
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
		return "Rockon";
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
		CurState_ = "Rockon";
	}
	else if (true == KeyState_Down_)
	{
		CurState_ = "Duck";
	}
	else if (true == KeyState_Right_ || true == KeyState_Left_)
	{
		CurState_ = "Walk";
	}

	CurState_ = "Idle";

	return CurState_;
}

//void Player::Shoot(float4 ShootDir)
//{
//	Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
//	NewBullet->SetMoveDir(ShootDir);
//	NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
//	NewBullet->Release(1.0f);
//}
//
//void Player::Shoot(float ShootDirX, float ShootDirY)
//{
//	Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
//	NewBullet->SetMoveDir(float4(ShootDirX, ShootDirY, 0.f));
//	NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
//	NewBullet->Release(1.0f);
//}

void Player::Move(float4 MoveDir, float _DeltaTime)
{
	GetTransform()->SetLocalMove(MoveDir * _DeltaTime);
}

void Player::Move(float DirX, float DirY, float _DeltaTime)
{
	GetTransform()->SetLocalMove(float4(DirX, DirY, 0.f) * _DeltaTime);
}

void Player::SpawnBullet(BulletType _Type, float4 _Dir)
{
	// 발사되는 방향에 맞게 로테이트 작업 해줘야함
	// 발사 오른쪽 왼쪽 잡아서 수평 회전시키기

	if (_Type == BulletType::Spread)
	{
		Bullet* _Bullet = GetLevel()->CreateActor<Bullet>();
		GameEngineTransformComponent* compo = _Bullet->CreateTransformComponent<GameEngineTransformComponent>();
		compo->GetTransform()->SetLocalPosition(GetBulletPoint());
		_Bullet->SetType(_Type);
		_Bullet->SetMoveDir(_Dir);

		_Bullet = GetLevel()->CreateActor<Bullet>();
		compo = _Bullet->CreateTransformComponent<GameEngineTransformComponent>();
		compo->GetTransform()->SetLocalPosition(GetBulletPoint());
		_Bullet->SetType(_Type);
		_Bullet->SetMoveDir(_Dir);
		compo->GetTransform()->SetLocalRotation(45.f, 0.f);

		_Bullet = GetLevel()->CreateActor<Bullet>();
		compo = _Bullet->CreateTransformComponent<GameEngineTransformComponent>();
		compo->GetTransform()->SetLocalPosition(GetBulletPoint());
		_Bullet->SetType(_Type);
		_Bullet->SetMoveDir(_Dir);
		compo->GetTransform()->SetLocalRotation(-45.f, 0.f);

	}
	else
	{
		Bullet* _Bullet = GetLevel()->CreateActor<Bullet>();
		GameEngineTransformComponent* compo = _Bullet->CreateTransformComponent<GameEngineTransformComponent>();
		compo->GetTransform()->SetLocalPosition(GetBulletPoint());
		_Bullet->SetType(_Type);
		_Bullet->SetMoveDir(_Dir);
	}
}

float4 Player::GetBulletPoint()
{
	return BulletPoint_->GetTransform()->GetLocalPosition();
}



