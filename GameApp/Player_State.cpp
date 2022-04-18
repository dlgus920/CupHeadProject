#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"
//#include <GameEngine/GameEngineImageRenderer.h>


void Player::Idle_Start()
{
	ChangeAnimation("Cup-Idle");
}
StateInfo Player::Idle_Update(StateInfo _state, float _DeltaTime)
{
	//StateUpdate(_DeltaTime);

	if (CheckState() != "Idle")
	{
		return CheckState();
	}

	if (KeyState_Shoot_)
	{
		ShootingInterTime_ += _DeltaTime;
		
		if (true == KeyState_Up_)
		{
			if (Dir_ == AnimationDirection::Left)
			{
				ChangeAnimation("Cup-Shoot-Up");
				BulletInfo_.MoveDir_ = float4::UP;
				ShootingDir_ = ShootingDir::Up_Left;
			}
			else
			{
				ChangeAnimation("Cup-Shoot-Up");
				BulletInfo_.MoveDir_ = float4::UP;
				ShootingDir_ = ShootingDir::Up_Right;
			}
		}

		else if (Dir_ == AnimationDirection::Left)
		{
			ChangeAnimation("Cup-Shoot-Str");
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left;
		}

		else if(Dir_ == AnimationDirection::Right)
		{
			ChangeAnimation("Cup-Shoot-Str");
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right;
		}

		if (ShootingInterTime_ >= 0.2f)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}
	else
	{
		ShootingInterTime_ = 0.f;

		ChangeAnimation("Cup-Idle");
	}

	return StateInfo();
}
void Player::Idle_End()
{
	ShootingInterTime_ = 0.f;
	TimeCheck_ = 0.f;
}

void Player::Walk_Start()
{
	
	// 각기 다른 에니메이션 재생
}
StateInfo Player::Walk_Update(StateInfo _state, float _DeltaTime)
{
	if (true == WalkState_Changed_)
	{
		ChangeAnimation("Cup-Walk-Turn");
	}

	if (CheckState() != "Walk")
	{
		return CheckState();
	}

	if (false == WalkState_Changed_)
	{

		if (KeyState_Shoot_)
		{
			ShootingInterTime_ += _DeltaTime;

			ChangeAnimation("Cup-Walk-Shoot-Str");

			if (Dir_ == AnimationDirection::Left)
			{
				BulletInfo_.MoveDir_ = float4::LEFT;
				ShootingDir_ = ShootingDir::Left;
			}
			else
			{
				BulletInfo_.MoveDir_ = float4::RIGHT;
				ShootingDir_ = ShootingDir::Right;
			}

			if (ShootingInterTime_ >= 0.2f)
			{
				BulletShootFunc_();
				ShootingInterTime_ = 0.f;
			}
		}
		else
		{
			ShootingInterTime_ = 0.f;

			ChangeAnimation("Cup-Walk");
		}

		if (KeyState_Right_)
		{
			Move(400.f, 0.f, _DeltaTime);
		}
		else
		{
			Move(-400.f, 0.f, _DeltaTime);
		}
	}
	return StateInfo();
}
void Player::Walk_End()
{
	ShootingInterTime_ = 0.f;
}

void Player::Jump_Start()
{
	ChangeAnimation("Cup-Jump");

	Move(0.f, 10.f, 0.f);

	Jumpend_ = false;
	LongJump_ = false;
	Parry_ = false;
	JumpSpeed_ = 0.f;
	TimeCheck_ = 0.f;
	ShootingInterTime_ = 0.f;

	JumpAcc_ = C_JumpSpeed0_ / 0.35f;


}
StateInfo Player::Jump_Update(StateInfo _state, float _DeltaTime)
{
	//TODO :: 언젠가 점프 더 부드럽게 다듬을것

	if (true == ColState_Hit_)
	{
		TimeCheck_ = 0.f;
		return "Hit";
	}

	if (true == KeyState_Dash_) 
	{
		TimeCheck_ = 0.f;
		return "Dash";
	}

	if (true == KeyState_Bomb)
	{
		TimeCheck_ = 0.f;
		return "Bomb";
	}

	TimeCheck_ += _DeltaTime;

	if (true == ColState_Parry_)
	{
		if (false == Parry_)
		{
			if (GameEngineInput::GetInst().Down("Jump"))
			{
				Parry_ = true; // 페리중이다.

				ChangeAnimation("Cup-Jump-Parry");

				Bottom_Card_->Increase();
				
				Jumpend_ = false;
				LongJump_ = false;
				JumpSpeed_ = 0.f;
				TimeCheck_ = 0.f;
			}
		}
	}

	if (true == Parry_)
	{
		if (TimeCheck_ < 0.35f)
		{
			JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
			Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
		}

		else if (TimeCheck_ >= 0.35f)
		{
			if (false == Jumpend_)
			{
				Jumpend_ = true;
				JumpSpeed_ = 0.f;
			}

			Parry_ = false;
		}
	}

	if (false == Parry_)
	{
		if (TimeCheck_ < 0.2f)
		{
			if (true == KeyState_Jump_Press)
			{
				LongJump_ = true;
			}
			else
			{
				LongJump_ = false;
			}
			JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
			Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
		}

		else if(TimeCheck_ >= 0.2f)
		{
			if (true == LongJump_)
			{
				if (TimeCheck_ < 0.30f)
				{
					Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
				}

				else if (TimeCheck_ < 0.45f)
				{
					JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
					Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
				}

				if (TimeCheck_ >= 0.55f)
				{
					if (false == Jumpend_)
					{
						Jumpend_ = true;
						JumpSpeed_ = 0.f;
					}

					JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
					Move(float4(0.f, JumpSpeed_, 0.f), _DeltaTime);

					if (Map::PixelCollisionTransform(PlayerMovingCollision, 10).b_Down)
					{
						TimeCheck_ = 0.f;
						return "Idle";
					}
				}
			}

			else if (false == LongJump_)
			{
				//TODO:: 여ㅣ서 0.35초 만큼의 ACC 조정이 필요해짐
				if (TimeCheck_ < 0.35f)
				{	
					JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
					Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
				}

				if (TimeCheck_ >= 0.35f)
				{
					if (false == Jumpend_)
					{
						Jumpend_ = true;
						JumpSpeed_ = 0.f;
					}

					JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
					Move(float4(0.f, JumpSpeed_, 0.f), _DeltaTime);

					if (Map::PixelCollisionTransform(PlayerMovingCollision, 10).b_Down)
					{
						TimeCheck_ = 0.f;
						return "Idle";
					}
				}
			}
		}
	}

	if (KeyState_Right_)
	{
		Move(C_MoveSpeed_,0.f,_DeltaTime);
	}
	else if (KeyState_Left_)
	{
		Move(-C_MoveSpeed_,0.f,_DeltaTime);
	}
	if (KeyState_Shoot_)
	{
		ShootingInterTime_ += _DeltaTime;

		if (Dir_ == AnimationDirection::Left)
		{
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left;
		}
		else
		{
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right;
		}

		if (ShootingInterTime_ >= 0.2f)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}
	else
	{
		ShootingInterTime_ = 0.f;
	}

	return StateInfo();
}
void Player::Jump_End()
{
	Jumpend_ = false;
	LongJump_ = false;
	Parry_ = false;
	JumpSpeed_ = 0.f;
	TimeCheck_ = 0.f;
	ShootingInterTime_ = 0.f;
}

void Player::Duck_Start()
{
	ChangeAnimation("Cup-Duck-Idle");
}
StateInfo Player::Duck_Update(StateInfo _state, float _DeltaTime)
{
	if (CheckState() != "Duck")
	{
		return CheckState();
	}

	if (KeyState_Shoot_)
	{
		ShootingInterTime_ += _DeltaTime;

		ChangeAnimation("Cup-Duck-Shoot");
		if (Dir_ == AnimationDirection::Right)
		{
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right_Down;
		}
		else
		{
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left_Down;
		}

		if (ShootingInterTime_ >= 0.2f)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}
	else
	{
		ChangeAnimation("Cup-Duck-Idle");
		ShootingInterTime_ = 0.f;
	}

	return StateInfo();
}
void Player::Duck_End()
{
	ShootingInterTime_ = 0.f;
}

void Player::RockOn_Start()
{
}
StateInfo Player::RockOn_Update(StateInfo _state, float _DeltaTime)
{
	if (CheckState() != "RockOn")
	{
		return CheckState();
	}

	if (true == KeyState_Shoot_)
	{
		ShootingInterTime_ += _DeltaTime;

		if (KeyState_Down_ && !KeyState_Up_)
		{
			if (Dir_ == AnimationDirection::Left)
			{
				if (true == KeyState_Left_)
				{
					ChangeAnimation("Cup-Shoot-Down-Str");
					BulletInfo_.MoveDir_ = float4::LEFTDOWN;
					ShootingDir_ = ShootingDir::Left_Down;
				}
				else
				{
					ChangeAnimation("Cup-Shoot-Down");
					BulletInfo_.MoveDir_ = float4::DOWN;
					ShootingDir_ = ShootingDir::Down_Left;
				}
			}

			else if (Dir_ == AnimationDirection::Right)
			{
				if (true == KeyState_Right_)
				{
					ChangeAnimation("Cup-Shoot-Down-Str");
					BulletInfo_.MoveDir_ = float4::RIGHTDOWN;
					ShootingDir_ = ShootingDir::Right_Down;
				}
				else
				{
					ChangeAnimation("Cup-Shoot-Down");
					BulletInfo_.MoveDir_ = float4::DOWN;
					ShootingDir_ = ShootingDir::Down_Right;
				}
			}
		}

		else if (KeyState_Up_ && !KeyState_Down_)
		{
			if (Dir_ == AnimationDirection::Left)
			{
				if (true == KeyState_Left_)
				{
					ChangeAnimation("Cup-Shoot-Up-Str");
					BulletInfo_.MoveDir_ = float4::LEFTUP;
					ShootingDir_ = ShootingDir::Left_Up;
				}
				else
				{
					ChangeAnimation("Cup-Shoot-Up");
					BulletInfo_.MoveDir_ = float4::UP;
					ShootingDir_ = ShootingDir::Up_Left;
				}
			}

			else if (Dir_ == AnimationDirection::Right)
			{
				if (true == KeyState_Right_)
				{
					ChangeAnimation("Cup-Shoot-Up-Str");
					BulletInfo_.MoveDir_ = float4::RIGHTUP;
					ShootingDir_ = ShootingDir::Right_Up;
				}
				else
				{
					ChangeAnimation("Cup-Shoot-Up");
					BulletInfo_.MoveDir_ = float4::UP;
					ShootingDir_ = ShootingDir::Up_Right;
				}
			}
		}

		else if (Dir_ == AnimationDirection::Left)
		{
			ChangeAnimation("Cup-Shoot-Str");
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left;
		}

		else if (Dir_ == AnimationDirection::Right)
		{
			ChangeAnimation("Cup-Shoot-Str");
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right;
		}

		if (ShootingInterTime_ >= 0.2f)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}

	else if(false == KeyState_Shoot_)
	{
		ShootingInterTime_ = 0.f;

		if (true == KeyState_Up_)
		{
			if (KeyState_Left_ ||
				KeyState_Right_)
			{
				ChangeAnimation("Cup-RockOn-Up-Str");			
			}

			else
			{
				ChangeAnimation("Cup-RockOn-Up");				
			}
		}

		else if (true == KeyState_Down_)
		{
			if (KeyState_Left_||
				KeyState_Right_)
			{
				ChangeAnimation("Cup-RockOn-Down-Str");
			}

			else
			{
				ChangeAnimation("Cup-RockOn-Down");
			}
		}

		else
		{
			ChangeAnimation("Cup-RockOn-Str");
		}
	}
	
	return StateInfo();
}
void Player::RockOn_End()
{
	ShootingInterTime_ = 0.f;
}

void Player::Bomb_Start()
{
	ChangeAnimation("Cup-Bomb");

}
StateInfo Player::Bomb_Update(StateInfo _state, float _DeltaTime)
{
	//if(ani end)
	{
		return CheckState();
	}
}
void Player::Bomb_End()
{
	TimeCheck_ = 0.f;
}

void Player::Death_Start()
{
	State_Update_ = false;
}
StateInfo Player::Death_Update(StateInfo _state, float _DeltaTime)
{
	if (true) // 조건 충족시
	{
		//return "Idle";
	}
	else
	{
		return StateInfo();

	}
	return StateInfo();
}
void Player::Death_End()
{
}

void Player::Hit_Start()
{
	if (true == ColState_Ground)
	{
		ChangeAnimation("Cup-Hit-Ground");
	}
	else
	{
		ChangeAnimation("Cup-Hit-Air");
	}

	HitInvince_ = true;

	Bottom_HP_->HPDecrease();
	TimeCheck_ = 0.f;

	JumpAcc_ = C_JumpSpeed0_ / 0.35f;
}
StateInfo Player::Hit_Update(StateInfo _state, float _DeltaTime)
{
	//if (Bottom_HP_->GetCurHP() == 0)
	//{
	//	return "Death";
	//}

	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ < 0.35f)
	{
		JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
		Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
	}

	else if (TimeCheck_ >= 0.35f)
	{
		JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
		Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);

		if (true == ColState_Ground)
		{
			return CheckState();
		}
	}
	//if aniend && ground
	

	return StateInfo();
}
void Player::Hit_End()
{
	JumpSpeed_ = 0.f;
	TimeCheck_ = 0.f;
}

void Player::Dash_Start()
{
	ChangeAnimation("Cup-Dash");
	TimeCheck_ = 0.f;
}
StateInfo Player::Dash_Update(StateInfo _state, float _DeltaTime)
{
	if ((Dir_ == AnimationDirection::Right))
	{
		Move(C_DashSpeed_, 0.f, _DeltaTime);
	}
	else
	{
		Move(-C_DashSpeed_, 0.f, _DeltaTime);
	}
	TimeCheck_ += _DeltaTime;

	if(TimeCheck_ > 1.f)
	{
		return CheckState();
	}

	return StateInfo();
}
void Player::Dash_End()
{
	TimeCheck_ = 0.f;
}

void Player::Parry_Start()
{
}

StateInfo Player::Parry_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}

void Player::Parry_End()
{
}