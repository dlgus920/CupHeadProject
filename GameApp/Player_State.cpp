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
		float4 dir;
		ChangeAnimation("Cup-Shoot-Str");

		if (Dir_ == AnimationDirection::Left)
		{
			dir = float4::LEFT;
		}
		else
		{
			dir = float4::RIGHT;
		}

		BulletShootFunc_(dir);
	}
	else
	{
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
		ChangeAnimation("Cup-Walk-Shoot-Str");

		float4 dir;

		if (Dir_ == AnimationDirection::Left)
		{
			dir = float4::LEFT;
		}
		else
		{
			dir = float4::RIGHT;
		}

		BulletShootFunc_(dir);
	}
	else
	{
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
