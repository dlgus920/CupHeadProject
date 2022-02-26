#include "PreCompile.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include "Player.h"
#include "Bullet.h"

Player::Player() :
	State_(this),
	PlayerImageRenderer(nullptr),
	Dir_(Dir::Right),
	KeyDir_(KeyDir::None),
	Key_Up_(false),
	Key_Down_(false),
	Key_Left_(false),
	Key_Right_(false),
	Key_RockOn_(false),
	Key_Shoot_(false),
	Key_Bomb(false),
	Key_Jump_(false),
	Key_Hit_(false),
	Key_Dash_(false),
	MoveDir_()

{
}

Player::~Player()
{
}


void Player::Start()
{
	RendererSetting();
	TransformSetting();
	KeySetting();
	StateSetting();
}

void Player::Update(float _DeltaTime)
{
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	KeyUpdate(_DeltaTime);
	CollisonUpdate();
	StateUpdate(_DeltaTime);
	if (false == State_Ground)
	{
		GravityUpdate(_DeltaTime);
	}
}

void Player::StateUpdate(float _DeltaTime)
{
	if (true == State_Hit_)
	{
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
	else if (true == Key_Bomb)
	{
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
	else if (true == Key_Jump_)
	{
		if (Key_Right_)
		{
			Move(_DeltaTime, 1.f, 0.f);
			Shoot(1.f, 0.f);
			return;
		}
		else if (Key_Left_)
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
	else if (true == Key_Dash_)
	{
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
	else if (true == Key_RockOn_)
	{
		if (true == Key_Shoot_) // ½î´ÂÁß
		{
			if (Key_Up_)
			{
				if (Key_Left_)
				{
					//RockOn_UpLeft_Shoot
					Shoot(1.f, -1.f);
					return;
				}
				else if (Key_Right_)
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
			else if (Key_Down_)
			{
				if (Key_Left_)
				{
					//RockOn_DownLeft_Shoot
					Shoot(-1.f, 0.f);
					return;
				}
				else if (Key_Right_)
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
			if (Key_Up_)
			{
				if (Key_Left_)
				{
					//RockOn_UpLeft_
					return;
				}
				else if (Key_Right_)
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
			else if (Key_Down_)
			{
				if (Key_Left_)
				{
					//RockOn_DownLeft_
					return;
				}
				else if (Key_Right_)
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
	else if (true == Key_Down_)
	{
		if (true == Key_Shoot_) // ½î´ÂÁß
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
	else if (true == Key_Right_)
	{
		if (true == Key_Shoot_)
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
	else if (true == Key_Left_)
	{
		if (true == Key_Shoot_)
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
	else if (true == Key_Shoot_)
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

	State_.Update(_DeltaTime);
}

void Player::KeyUpdate(float _DeltaTime)
{
	Key_Left_ = GameEngineInput::GetInst().Down("MoveLeft");
	Key_Right_ = GameEngineInput::GetInst().Down("MoveRight");

	if(Key_Left_)
		Dir_ = Dir::Left;

	if(Key_Right_)
		Dir_ = Dir::Right;

	Key_Up_ = GameEngineInput::GetInst().Down("MoveUp");
	Key_Down_ = GameEngineInput::GetInst().Down("MoveDown");

	Key_Shoot_ = GameEngineInput::GetInst().Down("Fire");

	Key_Bomb = GameEngineInput::GetInst().Down("Bomb");
	Key_Jump_ = GameEngineInput::GetInst().Down("Jump");
	Key_Dash_ = GameEngineInput::GetInst().Down("Dash");
	Key_RockOn_ = GameEngineInput::GetInst().Down("RockOn");

	//if (true == Key_Shoot_)
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
}

void Player::GravityUpdate(float _DeltaTime)
{
	GetTransform()->SetLocalMove(float4::DOWN * _DeltaTime);
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


