#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player.h"
#include "Bullet.h"

Player::Player() :
	State_(this),
	PlayerImageRenderer(nullptr),
	Dir_(Dir::Right),
	KeyDir_(KeyDir::None),
	KetState_Up_(false),
	KetState_Down_(false),
	KetState_Left_(false),
	KetState_Right_(false),
	KetState_RockOn_(false),
	KetState_Shoot_(false),
	KetState_Bomb(false),
	KetState_Jump_(false),
	KetState_Hit_(false),
	KetState_Dash_(false),
	ColState_Ground(false),
	ColState_Hit_(false),
	MoveDir_()

{
}

Player::~Player()
{
}


void Player::Start()
{
	ComponentSetting();
	RendererSetting();
	CollisionSetting();
	TransformSetting();
	KeySetting();
	StateSetting();
}

void Player::Update(float _DeltaTime)
{
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
	
	KeyUpdate(_DeltaTime);
	CollisonUpdate(); // 컬리젼 업데이트에서 상대방과 충돌 여부를 검사하고, stateupdate에서ㅏ 참고하도록 한다.
	State_.Update(_DeltaTime);
	StateUpdate(_DeltaTime);

	if (true == State_Update_)
	{
		KeyStateUpdate(_DeltaTime);
	}

	if (false == ColState_Ground)
	{
		GravityUpdate(_DeltaTime);
	}
}
void Player::StateUpdate(float _DeltaTime)
{
	State_Update_ = true;
}

void Player::KeyStateUpdate(float _DeltaTime)
{
	if (true == ColState_Hit_)
	{
		State_.ChangeState("Hit");
		if (Dir_ == Dir::Left)
		{
			//Hit_Left
			return;
		}
		else
		{
			//Hit_Right
			return;
		}
	}
	else if (true == KetState_Bomb)
	{
		State_.ChangeState("Bomb");
		if (Dir_ == Dir::Left)
		{
			//Bomb_Left
			return;
		}
		else
		{
			//Bomb_Right
			return;
		}
	}
	else if (true == KetState_Jump_)
	{
		State_.ChangeState("Jump");

		if (KetState_Right_)
		{
			Move(_DeltaTime, 1.f, 0.f);
			Shoot(1.f, 0.f);
			return;
		}
		else if (KetState_Left_)
		{
			Move(_DeltaTime, -1.f, 0.f);
			Shoot(-1.f, 0.f);
			return;
		}
		else if (Dir_ == Dir::Left)
		{
			//Jump_Left
			Shoot(-1.f, 0.f);
			return;
		}
		else
		{
			//Jump_Right
			Shoot(1.f, 0.f);
			return;
		}
	}
	else if (true == KetState_Dash_)
	{
		State_.ChangeState("Dash");
		if (Dir_ == Dir::Left)
		{
			//Dash_Left
			return;
		}
		else
		{
			//Dash_Right
			return;
		}
	}
	else if (true == KetState_RockOn_)
	{
		if (true == KetState_Shoot_) // 쏘는중
		{
			if (KetState_Up_)
			{
				if (KetState_Left_)
				{
					//RockOn_UpLeft_Shoot
					Shoot(1.f, -1.f);
					return;
				}
				else if (KetState_Right_)
				{
					//RockOn_UpRight_Shoot
					Shoot(1.f, 1.f);
					return;
				}

				else
				{
					if (Dir_ == Dir::Left)
					{
						//RockOn_LeftUp_Shoot
						Shoot(1.f, 0.f);
						return;
					}
					else
					{
						//RockOn_RightUp_Shoot
						Shoot(1.f, 0.f);
						return;
					}
				}
			}
			else if (KetState_Down_)
			{
				if (KetState_Left_)
				{
					//RockOn_DownLeft_Shoot
					Shoot(-1.f, 0.f);
					return;
				}
				else if (KetState_Right_)
				{
					//RockOn_DownRight_Shoot
					Shoot(-1.f, 0.f);
					return;
				}

				else
				{
					if (Dir_ == Dir::Left)
					{
						//RockOn_LeftDown_Shoot
						Shoot(-1.f, -1.f);
						return;
					}
					else
					{
						//RockOn_RightDown_Shoot
						Shoot(-1.f, 1.f);
						return;
					}
				}
			}
		}
		else
		{
			if (KetState_Up_)
			{
				if (KetState_Left_)
				{
					//RockOn_UpLeft_
					return;
				}
				else if (KetState_Right_)
				{
					//RockOn_UpRight_
					return;
				}
				else
				{
					if (Dir_ == Dir::Left)
					{
						//RockOn_LeftUp_
						return;
					}
					else
					{
						//RockOn_RightUp_
						return;
					}
				}
			}
			else if (KetState_Down_)
			{
				if (KetState_Left_)
				{
					//RockOn_DownLeft_
					return;
				}
				else if (KetState_Right_)
				{
					//RockOn_DownRight_
					return;
				}
				else
				{
					if (Dir_ == Dir::Left)
					{
						//RockOn_LeftDown_
						return;
					}
					else
					{
						//RockOn_RightDown_
						return;
					}
				}
			}
		}
	}
	else if (true == KetState_Down_)
	{
		if (true == KetState_Shoot_) // 쏘는중
		{
			if (Dir_ == Dir::Left)
			{
				//Duck_Left_Shoot
				Shoot(0.f, -1.f);
				return;
			}
			else
			{
				//Duck_Right_Shoot
				Shoot(0.f, 1.f);
				return;
			}
		}
		else
		{
			if (Dir_ == Dir::Left)
			{
				//Duck_Left_
				return;
			}
			else
			{
				//Duck_Right_
				return;
			}
		}
	}
	else if (true == KetState_Right_)
	{
		if (true == KetState_Shoot_)
		{
			//Walk_Right_Shoot
			Move(_DeltaTime, 1.f, 0.f);
			Shoot(0.f, 1.f);
			return;
		}
		else
		{
			//Walk_Right_
			Move(_DeltaTime, 1.f, 0.f);
			return;
		}
	}
	else if (true == KetState_Left_)
	{
		if (true == KetState_Shoot_)
		{
			Shoot(0.f, -1.f);
			Move(_DeltaTime, -1.f, 0.f);
			//Walk_Left_Shoot
			return;
		}
		else
		{
			//Walk_Left_
			Move(_DeltaTime, -1.f, 0.f);
			return;
		}
	}
	else if (true == KetState_Shoot_)
	{
		if (Dir_ == Dir::Left)
		{
			//Idle_Left_Shoot 
			Shoot(0.f, -1.f);
			return;
		}
		else
		{
			//Idle_Right_Shoot
			Shoot(0.f, 1.f);
			return;
		}
	}
}

void Player::KeyUpdate(float _DeltaTime)
{
	KetState_Left_ = GameEngineInput::GetInst().Down("MoveLeft");
	KetState_Right_ = GameEngineInput::GetInst().Down("MoveRight");

	if (KetState_Left_ && !KetState_Right_)
		Dir_ = Dir::Left;

	else if (KetState_Right_ && !KetState_Left_)
		Dir_ = Dir::Right;

	KetState_Up_ = GameEngineInput::GetInst().Down("MoveUp");
	KetState_Down_ = GameEngineInput::GetInst().Down("MoveDown");

	KetState_Shoot_ = GameEngineInput::GetInst().Down("Fire");

	KetState_Bomb = GameEngineInput::GetInst().Down("Bomb");
	KetState_Jump_ = GameEngineInput::GetInst().Down("Jump");
	KetState_Dash_ = GameEngineInput::GetInst().Down("Dash");
	KetState_RockOn_ = GameEngineInput::GetInst().Down("RockOn");

	//if (true == KetState_Shoot_)
	//{
	//	
	//	//Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
	//	//NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
	//	//NewBullet->Release(1.0f);
	//}

	//if (true == GameEngineInput::GetInst().Press("RotZ+"))
	//{
	//	PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	//}

	//if (true == GameEngineInput::GetInst().Press("RotZ-"))
	//{
	//	PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
	//}

}

void Player::CollisonUpdate()
{
	if (true) // TODO : 컬리전이 처음부터 bool 값으로 리턴되게끔
	{
		ColState_Ground = true;
	}
	else
	{
		ColState_Ground = false;
	}

	if (true)
	{
		ColState_Hit_ = true;
	}
	else
	{
		ColState_Hit_ = false;
	}

}

void Player::GravityUpdate(float _DeltaTime)
{
	GetTransform()->SetLocalMove(float4::DOWN * _DeltaTime);
}

void Player::ChangeAnimation(std::string _animation)
{
	PlayerImageRenderer->SetChangeAnimation(_animation);
	PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetTextureSize()); 
	//TODO: 근데 이거 혹시 안 잘라진 텍스처 크기 그대로 가져오나?
	// 아무래도 텍스처가 지 크기를 가지고 있는데 좋을거같다.
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


