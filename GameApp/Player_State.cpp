#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"
//#include <GameEngine/GameEngineImageRenderer.h>


StateInfo Player::Idle_Start(StateInfo _state)
{
	ChangeAnimation("Cup-Idle");

	return StateInfo();
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
		ChangeAnimation("Cup-Idle_Shoot");
	}
	else
	{
		ChangeAnimation("Cup-Idle");
	}

	return StateInfo();
}

StateInfo Player::Walk_Start(StateInfo _state)
{
	// 각기 다른 에니메이션 재생

	return StateInfo();
}
StateInfo Player::Walk_Update(StateInfo _state, float _DeltaTime)
{
	if (CheckState() != "Walk")
	{
		return CheckState();
	}

	if (KeyState_Shoot_)
	{
		ChangeAnimation("Cup-Walk_Shoot");
	}
	else
	{
		ChangeAnimation("Cup-Walk");
	}

	if (KeyState_Right_)
	{
		Move(100.f, 0.f, _DeltaTime);
	}
	else
	{
		Move(-100.f, 0.f, _DeltaTime);
	}

	return StateInfo();
}

StateInfo Player::Jump_Start(StateInfo _state)
{
	ChangeAnimation("Cup-Jump");

	return StateInfo();
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
	 
	GravitySpeed_ += GravityAcc_;

	Move(float4(0.f, -200.f + GravitySpeed_, 0.f), _DeltaTime);

	if (KeyState_Right_)
	{
		Move(200.f,0.f,_DeltaTime);
	}
	else if (KeyState_Left_)
	{
		Move(-200.f,0.f,_DeltaTime);
	}

	return StateInfo();
}

StateInfo Player::Duck_Start(StateInfo _state)
{
	ChangeAnimation("Duck-Idle");

	return StateInfo();
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

StateInfo Player::RockOn_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::RockOn_Update(StateInfo _state, float _DeltaTime)
{
	if (CheckState() != "RockOn")
	{
		return CheckState();
	}

	if (true == KeyState_Shoot_)
	{
		if (true == KeyState_Up_)
		{
			if (true == KeyState_Left_)
			{
				ChangeAnimation("Cup-Shoot-Up-Str");
			}
			else
			{
				ChangeAnimation("Cup-Shoot-Up");
			}
		}

		else if (true == KeyState_Down_)
		{
			if (true == KeyState_Left_)
			{
				ChangeAnimation("Cup-Shoot-Down-Str");
				SpawnBullet(BulletType_,float4::LEFT);
			}
			else
			{
				ChangeAnimation("Cup-Shoot-Down");
			}
		}
		ChangeAnimation("Cup-Shoot-Str");
	}

	else
	{
		if (true == KeyState_Up_)
		{
			if (true == KeyState_Left_)
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
			if (true == KeyState_Left_)
			{
				ChangeAnimation("Cup-RockOn-Down-Str");

			}
			else
			{
				ChangeAnimation("Cup-RockOn-Down");
			}
		}
		ChangeAnimation("Cup-RockOn-Str");
	}
	
	return StateInfo();
}

StateInfo Player::Bomb_Start(StateInfo _state)
{
	ChangeAnimation("Cup-Bomb");

	return StateInfo();
}

StateInfo Player::Bomb_Update(StateInfo _state, float _DeltaTime)
{
	//if(ani end)
	{
		return CheckState();
	}
}

StateInfo Player::Death_Start(StateInfo _state)
{
	State_Update_ = false;
	return StateInfo();
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

StateInfo Player::Hit_Start(StateInfo _state)
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
	return StateInfo();
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

StateInfo Player::Dash_Start(StateInfo _state)
{
	ChangeAnimation("Cup-Dash");
	TimeCheck_ = 0.f;

	return StateInfo();
}

StateInfo Player::Dash_Update(StateInfo _state, float _DeltaTime)
{
	Move(100.f,0.f,_DeltaTime);
	TimeCheck_ += _DeltaTime;


	if(TimeCheck_ > 1.f)
	{
		return CheckState();
	}
}
