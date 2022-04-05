#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"
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
			BulletInfo_.MoveDir_ = float4::UP;
			ChangeAnimation("Cup-Shoot-Up");
		}

		else if (Dir_ == AnimationDirection::Left)
		{
			BulletInfo_.MoveDir_ = float4::LEFT;
			ChangeAnimation("Cup-Shoot-Str");
		}
		else
		{
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ChangeAnimation("Cup-Shoot-Str");
		}

		if (ShootingInterTime_ >= 0.2f)
		{
			BulletShootFunc_(BulletInfo_);
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
}

void Player::Walk_Start()
{
	// 각기 다른 에니메이션 재생
}
StateInfo Player::Walk_Update(StateInfo _state, float _DeltaTime)
{
	if (CheckState() != "Walk")
	{
		return CheckState();
	}

	if (KeyState_Shoot_)
	{
		ShootingInterTime_ += _DeltaTime;

		ChangeAnimation("Cup-Walk-Shoot-Str");

		if (Dir_ == AnimationDirection::Left)
		{
			BulletInfo_.MoveDir_ = float4::LEFT;
		}
		else
		{
			BulletInfo_.MoveDir_ = float4::RIGHT;
		}

		if (ShootingInterTime_ >= 0.2f)
		{
			BulletShootFunc_(BulletInfo_);
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

	return StateInfo();
}
void Player::Walk_End()
{
}

void Player::Jump_Start()
{
	ChangeAnimation("Cup-Jump");

	Move(0.f, 10.f, 0.1f);
}
StateInfo Player::Jump_Update(StateInfo _state, float _DeltaTime)
{
	//TODO : 점프하고 올라갈때 내려갈때를 flag 하여 하단, 상단 컬리전을 키고 끈다.

	//std::string state = CheckState();

	//if (state != "Walk" || state != "Jump")
	//{
	//	GravitySpeed_ = 0.f;
	//	return state;
	//}

	if (true == ColState_Hit_)
	{
		GravitySpeed_ = 0.f;
		return "Hit";
	}

	if (true == KeyState_Dash_) 
	{
		GravitySpeed_ = 0.f;
		return "Dash";
	}

	if (true == KeyState_Bomb)
	{
		GravitySpeed_ = 0.f;
		return "Bomb";
	}

	if (true == ColState_Ground)
	{
		GravitySpeed_ = 0.f;
		return "Idle";
	}
	 
	if (false == ColState_Ground)
	{
		GravitySpeed_ -= GravityAcc_;

		if (GravitySpeed_ < -600.f)
		{
			GravitySpeed_ = -600.f;
		}

		Move(float4(0.f, 400.f + GravitySpeed_, 0.f), _DeltaTime);
	}

	if (KeyState_Right_)
	{
		Move(400.f,0.f,_DeltaTime);
	}
	else if (KeyState_Left_)
	{
		Move(-400.f,0.f,_DeltaTime);
	}

	if (KeyState_Shoot_)
	{
		ShootingInterTime_ += _DeltaTime;

		if (Dir_ == AnimationDirection::Left)
		{
			BulletInfo_.MoveDir_ = float4::LEFT;
		}
		else
		{
			BulletInfo_.MoveDir_ = float4::RIGHT;
		}

		if (ShootingInterTime_ >= 0.2f)
		{
			BulletShootFunc_(BulletInfo_);
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
	GravitySpeed_ = 0.f;

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
		ChangeAnimation("Cup-Duck-Shoot");
	}
	else
	{
		ChangeAnimation("Cup-Duck-Idle");
	}

	return StateInfo();
}
void Player::Duck_End()
{
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

		if (true == KeyState_Up_)
		{
			if (KeyState_Left_)
			{
				ChangeAnimation("Cup-Shoot-Up-Str");
				BulletInfo_.MoveDir_ = float4::UPLEFT;
			}

			else if (KeyState_Right_)
			{
				ChangeAnimation("Cup-Shoot-Up-Str");
				BulletInfo_.MoveDir_ = float4::UPRIGHT;
			}
			else
			{
				ChangeAnimation("Cup-Shoot-Up");
				BulletInfo_.MoveDir_ = float4::UP;
			}
		}

		else if (true == KeyState_Down_)
		{
			if (KeyState_Left_)
			{
				ChangeAnimation("Cup-Shoot-Down-Str");
				BulletInfo_.MoveDir_ = float4::DOWNLEFT;
			}

			else if(KeyState_Right_)
			{
				ChangeAnimation("Cup-Shoot-Down-Str");
				BulletInfo_.MoveDir_ = float4::DOWNRIGHT;
			}

			else
			{
				ChangeAnimation("Cup-Shoot-Down");
				BulletInfo_.MoveDir_ = float4::DOWN;
			}
		}

		else
		{
			ChangeAnimation("Cup-Shoot-Str");

			if (Dir_ == AnimationDirection::Right)
			{
				BulletInfo_.MoveDir_ = float4::RIGHT;
			}
			else
			{
				BulletInfo_.MoveDir_ = float4::LEFT;
			}
		}

		if (ShootingInterTime_ >= 0.2f)
		{
			BulletShootFunc_(BulletInfo_);
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

	TimeCheck_ = 0.f;
	GravitySpeed_ = 0.f;
}
StateInfo Player::Hit_Update(StateInfo _state, float _DeltaTime)
{
	TimeCheck_ += _DeltaTime;

	GravitySpeed_ += GravityAcc_;
	Move(float4(0.f, -200.f + GravitySpeed_, 0.f), _DeltaTime);

	//if aniend && ground
	if(TimeCheck_ > 1.f)
	{
		return CheckState();
	}

	return StateInfo();
}
void Player::Hit_End()
{
}

void Player::Dash_Start()
{
	ChangeAnimation("Cup-Dash");
	TimeCheck_ = 0.f;
}
StateInfo Player::Dash_Update(StateInfo _state, float _DeltaTime)
{
	Move(100.f,0.f,_DeltaTime);
	TimeCheck_ += _DeltaTime;


	if(TimeCheck_ > 1.f)
	{
		return CheckState();
	}

	return StateInfo();
}
void Player::Dash_End()
{
}
