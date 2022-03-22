#include "PreCompile.h"
#include "Player.h"


void Player::StateUpdate(float _DeltaTime)
{
	State_Update_ = true;
}

void Player::KeyStateUpdate(float _DeltaTime)
{
	if (true == ColState_Hit_)
	{
		State_.ChangeState("Hit");
	}
	else if (true == KeyState_Bomb)
	{
		State_.ChangeState("Bomb");
	}
	else if (true == KeyState_Jump_)
	{
		State_.ChangeState("Jump");
		// ????
		if (KeyState_Right_)
		{
			Move(_DeltaTime, 1.f, 0.f);
			Shoot(1.f, 0.f);
			return;
		}
		else if (KeyState_Left_)
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
	else if (true == KeyState_Dash_)
	{
		State_.ChangeState("Dash");
	}
	else if (true == KeyState_RockOn_)
	{
		if (true == KeyState_Shoot_) // 쏘는중
		{
			if (KeyState_Up_)
			{
				if (KeyState_Left_)
				{
					//RockOn_UpLeft_Shoot
					Shoot(1.f, -1.f);
					return;
				}
				else if (KeyState_Right_)
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
			else if (KeyState_Down_)
			{
				if (KeyState_Left_)
				{
					//RockOn_DownLeft_Shoot
					Shoot(-1.f, 0.f);
					return;
				}
				else if (KeyState_Right_)
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
			if (KeyState_Up_)
			{
				if (KeyState_Left_)
				{
					//RockOn_UpLeft_
					return;
				}
				else if (KeyState_Right_)
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
			else if (KeyState_Down_)
			{
				if (KeyState_Left_)
				{
					//RockOn_DownLeft_
					return;
				}
				else if (KeyState_Right_)
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
	else if (true == KeyState_Down_)
	{
		if (true == KeyState_Shoot_) // 쏘는중
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
		}
	}
	else if (true == KeyState_Right_)
	{
		if (true == KeyState_Shoot_)
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
	else if (true == KeyState_Left_)
	{
		if (true == KeyState_Shoot_)
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
	else if (true == KeyState_Shoot_)
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
	KeyState_Left_ = GameEngineInput::GetInst().Down("MoveLeft");
	KeyState_Right_ = GameEngineInput::GetInst().Down("MoveRight");

	if (KeyState_Left_ && !KeyState_Right_)
	{
		if (Dir_ == AnimationDirection::Left)
			GetTransform()->SetHorizenInvertTransform();
		Dir_ = AnimationDirection::Right;
	}

	else if (KeyState_Right_ && !KeyState_Left_)
	{
		if (Dir_ == AnimationDirection::Right)
			GetTransform()->SetHorizenInvertTransform();
		Dir_ = AnimationDirection::Left;
	}

	KeyState_Up_ = GameEngineInput::GetInst().Down("MoveUp");
	KeyState_Down_ = GameEngineInput::GetInst().Down("MoveDown");

	KeyState_Shoot_ = GameEngineInput::GetInst().Down("Fire");

	KeyState_Bomb = GameEngineInput::GetInst().Down("Bomb");
	KeyState_Jump_ = GameEngineInput::GetInst().Down("Jump");
	KeyState_Dash_ = GameEngineInput::GetInst().Down("Dash");
	KeyState_RockOn_ = GameEngineInput::GetInst().Down("RockOn");

	//if (true == KeyState_Shoot_)
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

