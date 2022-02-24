#include "PreCompile.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include "Player.h"
#include "Bullet.h"

Player::Player() :
	State_(this),
	PlayerImageRenderer(nullptr),
	Move_Info_(Player_Move_Info::Idle),
	Act_Info_(Player_Act_Info::None),
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
	KeyUpdate(_DeltaTime);
	StateUpdate(_DeltaTime);
	CollisonUpdate();
}

void Player::StateUpdate(float _DeltaTime)
{
	if (Key_Bomb)
	{
		State_.ChangeState("Bomb");
	}
	else if (Key_Dash_)
	{
		State_.ChangeState("Dash");
	}

	else if (Key_RockOn_)
	{
		State_.ChangeState("RockOn");
	}
	else if (Key_Jump_)
	{
		State_.ChangeState("Jump");
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


	if (true == State_Hit_)
	{
		if (Dir_ == Dir::Left)
		{
			//Hit_Left
		}
		else
		{
			//Hit_Right
		}
	}
	else if (true == Key_Bomb)
	{
		if (Dir_ == Dir::Left)
		{
			//Bomb_Left
		}
		else
		{
			//Bomb_Right
		}
	}
	else if (true == Key_Jump_)
	{	
		if (Key_Right_)
		{
			Move(_DeltaTime, 1.f, 0.f);
			Shoot(1.f, 0.f);
		}
		else if (Key_Left_)
		{
			Move(_DeltaTime, -1.f, 0.f);
			Shoot(-1.f, 0.f);
		}
		else if (Dir_ == Dir::Left)
		{
			//Jump_Left
			Shoot(-1.f, 0.f);
		}
		else
		{
			//Jump_Right
			Shoot(1.f, 0.f);
		}
	}
	else if (true == Key_Dash_)
	{
		if (Dir_ == Dir::Left)
		{
			//Dash_Left
		}
		else
		{
			//Dash_Right
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
				}
				else if (Key_Right_)
				{
					//RockOn_UpRight_Shoot
					Shoot(1.f, 1.f);
				}

				else
				{
					if (Dir_ == Dir::Left)
					{
						//RockOn_LeftUp_Shoot
						Shoot(1.f, 0.f);
					}
					else
					{
						//RockOn_RightUp_Shoot
						Shoot(1.f, 0.f);
					}
				}
			}
			else if (Key_Down_)
			{
				if (Key_Left_)
				{
					//RockOn_DownLeft_Shoot
					Shoot(-1.f, 0.f);
				}
				else if (Key_Right_)
				{
					//RockOn_DownRight_Shoot
					Shoot(-1.f, 0.f);
				}

				else
				{
					if (Dir_ == Dir::Left)
					{
						//RockOn_LeftDown_Shoot
						Shoot(-1.f, -1.f);
					}
					else
					{
						//RockOn_RightDown_Shoot
						Shoot(-1.f, 1.f);
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
				}
				else if (Key_Right_)
				{
					//RockOn_UpRight_
				}

				else
				{
					if (Dir_ == Dir::Left)
					{
						//RockOn_LeftUp_
					}
					else
					{
						//RockOn_RightUp_
					}
				}
			}
			else if (Key_Down_)
			{
				if (Key_Left_)
				{
					//RockOn_DownLeft_
				}
				else if (Key_Right_)
				{
					//RockOn_DownRight_
				}

				else
				{
					if (Dir_ == Dir::Left)
					{
						//RockOn_LeftDown_
					}
					else
					{
						//RockOn_RightDown_
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
			}
			else
			{
				//Duck_Right_Shoot
				Shoot(0.f, 1.f);
			}
		}
		else
		{
			if (Dir_ == Dir::Left)
			{
				//Duck_Left_
			}
			else
			{
				//Duck_Right_
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
		}
		else
		{
			//Walk_Right_
			Move(_DeltaTime, 1.f, 0.f);
		}
	}
	else if (true == Key_Left_)
	{
		if (true == Key_Shoot_)
		{
			Shoot(0.f, -1.f);
			Move(_DeltaTime, -1.f, 0.f);
			//Walk_Left_Shoot
		}
		else
		{
			//Walk_Left_
			Move(_DeltaTime, -1.f, 0.f);
		}
	}
	else if (true == Key_Shoot_)
	{
		if (Dir_ == Dir::Left)
		{
			//Idle_Left_Shoot 
			Shoot(0.f, -1.f);
		}
		else
		{
			//Idle_Right_Shoot
			Shoot(0.f, 1.f);
		}
	}

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
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
}

void Player::CollisonUpdate()
{
}

void Player::Gravity()
{
}

void Player::Shoot(float4 ShootDir)
{
}

void Player::Shoot(float ShootDirX, float ShootDirY)
{
}

void Player::Move(float _DeltaTime, float4 MoveDir)
{
}

void Player::Move(float _DeltaTime, float ShootDirX, float ShootDirY)
{
}


