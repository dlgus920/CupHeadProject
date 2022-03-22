#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Bullet.h"
#include "Map.h"

Player::Player() :
	State_(this),
	AnimationState_(this),
	PlayerImageRenderer(nullptr),
	KeyDir_(KeyDir::None),
	KeyState_Update_(true),
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
	ColState_Update_(true),
	ColState_Ground(false),
	ColState_Hit_(false),
	State_Update_(true),
	MoveDir_()

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
	RendererSetting();
	AnimationSetting();
	CollisionSetting();
	//TransformSetting();
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
	KeyStateUpdate(_DeltaTime); // 사실상 key와 별개인ㄴㅁ

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

void Player::ChangeAnimation()
{
	//if (true == ColState_Hit_)
	//{
	//	State_.ChangeState("Hit");
	//}
	//else if (true == KeyState_Bomb)
	//{
	//	State_.ChangeState("Bomb");
	//}
	//else if (true == KeyState_Jump_)
	//{
	//	State_.ChangeState("Jump");
	//	// ????
	//	if (KeyState_Right_)
	//	{
	//		Move(_DeltaTime, 1.f, 0.f);
	//		Shoot(1.f, 0.f);
	//		return;
	//	}
	//	else if (KeyState_Left_)
	//	{
	//		Move(_DeltaTime, -1.f, 0.f);
	//		Shoot(-1.f, 0.f);
	//		return;
	//	}
	//	else if (Dir_ == Dir::Left)
	//	{
	//		//Jump_Left
	//		Shoot(-1.f, 0.f);
	//		return;
	//	}
	//	else
	//	{
	//		//Jump_Right
	//		Shoot(1.f, 0.f);
	//		return;
	//	}
	//}
	//else if (true == KeyState_Dash_)
	//{
	//	State_.ChangeState("Dash");
	//}
	//else if (true == KeyState_RockOn_)
	//{
	//	if (true == KeyState_Shoot_) // 쏘는중
	//	{
	//		if (KeyState_Up_)
	//		{
	//			if (KeyState_Left_)
	//			{
	//				//RockOn_UpLeft_Shoot
	//				Shoot(1.f, -1.f);
	//				return;
	//			}
	//			else if (KeyState_Right_)
	//			{
	//				//RockOn_UpRight_Shoot
	//				Shoot(1.f, 1.f);
	//				return;
	//			}
	//
	//			else
	//			{
	//				if (Dir_ == Dir::Left)
	//				{
	//					//RockOn_LeftUp_Shoot
	//					Shoot(1.f, 0.f);
	//					return;
	//				}
	//				else
	//				{
	//					//RockOn_RightUp_Shoot
	//					Shoot(1.f, 0.f);
	//					return;
	//				}
	//			}
	//		}
	//		else if (KeyState_Down_)
	//		{
	//			if (KeyState_Left_)
	//			{
	//				//RockOn_DownLeft_Shoot
	//				Shoot(-1.f, 0.f);
	//				return;
	//			}
	//			else if (KeyState_Right_)
	//			{
	//				//RockOn_DownRight_Shoot
	//				Shoot(-1.f, 0.f);
	//				return;
	//			}
	//
	//			else
	//			{
	//				if (Dir_ == Dir::Left)
	//				{
	//					//RockOn_LeftDown_Shoot
	//					Shoot(-1.f, -1.f);
	//					return;
	//				}
	//				else
	//				{
	//					//RockOn_RightDown_Shoot
	//					Shoot(-1.f, 1.f);
	//					return;
	//				}
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (KeyState_Up_)
	//		{
	//			if (KeyState_Left_)
	//			{
	//				//RockOn_UpLeft_
	//				return;
	//			}
	//			else if (KeyState_Right_)
	//			{
	//				//RockOn_UpRight_
	//				return;
	//			}
	//			else
	//			{
	//				if (Dir_ == Dir::Left)
	//				{
	//					//RockOn_LeftUp_
	//					return;
	//				}
	//				else
	//				{
	//					//RockOn_RightUp_
	//					return;
	//				}
	//			}
	//		}
	//		else if (KeyState_Down_)
	//		{
	//			if (KeyState_Left_)
	//			{
	//				//RockOn_DownLeft_
	//				return;
	//			}
	//			else if (KeyState_Right_)
	//			{
	//				//RockOn_DownRight_
	//				return;
	//			}
	//			else
	//			{
	//				if (Dir_ == Dir::Left)
	//				{
	//					//RockOn_LeftDown_
	//					return;
	//				}
	//				else
	//				{
	//					//RockOn_RightDown_
	//					return;
	//				}
	//			}
	//		}
	//	}
	//}
	//else if (true == KeyState_Down_)
	//{
	//	if (true == KeyState_Shoot_) // 쏘는중
	//	{
	//		if (Dir_ == Dir::Left)
	//		{
	//			//Duck_Left_Shoot
	//			Shoot(0.f, -1.f);
	//			return;
	//		}
	//	}
	//	else
	//	{
	//	}
	//}
	//else if (true == KeyState_Right_)
	//{
	//	if (true == KeyState_Shoot_)
	//	{
	//		//Walk_Right_Shoot
	//		ChangeAnimation("");
	//		
	//		return;
	//	}
	//	ChangeAnimation("");
	//}
	//else if (true == KeyState_Left_)
	//{
	//	if (true == KeyState_Shoot_)
	//	{
	//		Shoot(0.f, -1.f);
	//		Move(_DeltaTime, -1.f, 0.f);
	//		//Walk_Left_Shoot
	//		return;
	//	}
	//}
	//else if (true == KeyState_Shoot_)
	//{
	//	if (Dir_ == Dir::Left)
	//	{
	//		//Idle_Left_Shoot 
	//		Shoot(0.f, -1.f);
	//		return;
	//	}
	//}
}

void Player::ChangeState()
{
	if (true == ColState_Hit_)
	{
		State_.ChangeState("Hit");
		return;
	}
	else if (true == KeyState_Bomb)
	{
		State_.ChangeState("Bomb");
		return;
	}
	else if (true == KeyState_Jump_)
	{
		State_.ChangeState("Jump");
		return;
	}
	else if (true == KeyState_Dash_)
	{
		State_.ChangeState("Dash");
		return;
	}
	else if (true == KeyState_RockOn_)
	{
		State_.ChangeState("RockOn");
		return;
	}
	else if (true == KeyState_Down_)
	{
		State_.ChangeState("Duck");
		return;
	}
	else if (true == KeyState_Right_ || true == KeyState_Left_)
	{
		State_.ChangeState("Walk");
		return;
	}
}

void Player::Shoot(float4 ShootDir)
{
	Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
	NewBullet->SetMoveDir(ShootDir);
	NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
	NewBullet->Release(1.0f);
}

void Player::Shoot(float ShootDirX, float ShootDirY)
{
	Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
	NewBullet->SetMoveDir(float4(ShootDirX, ShootDirY, 0.f));
	NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
	NewBullet->Release(1.0f);
}

void Player::Move(float4 MoveDir, float _DeltaTime)
{
	GetTransform()->SetLocalMove(MoveDir * _DeltaTime);
}

void Player::Move(float DirX, float DirY, float _DeltaTime)
{
	GetTransform()->SetLocalMove(float4(DirX, DirY, 0.f) * _DeltaTime);
}



