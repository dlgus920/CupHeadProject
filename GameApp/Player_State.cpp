#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player.h"

#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player.h"


StateInfo Player::Idle_Start(StateInfo _state)
{
	return StateInfo();
}
StateInfo Player::Idle_Update(StateInfo _state, float _DeltaTime)
{
	//state 시스템 없앨까 고민중

	

	return StateInfo();
}

StateInfo Player::Walk_Start(StateInfo _state)
{
	// 각기 다른 에니메이션 재생

	return StateInfo();
}
StateInfo Player::Walk_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}

StateInfo Player::Jump_Start(StateInfo _state)
{
	return StateInfo();
}
StateInfo Player::Jump_Update(StateInfo _state, float _DeltaTime)
{
	if (true == Key_Bomb)
	{
		return "Bomb";
	}
	else if (true == Key_Dash_)
	{
		return "Dash";
	}
	if (!(Key_Up_ && Key_Down_ && Key_Right_ && Key_Left_))
	{
		return "Idle";
	}


	if (true == Key_Shoot_) // 쏘는중
	{
		//ShootJump();
	}
	else
	{

	}

	if (Key_Right_)
	{
		
	}
	else if (Key_Left_)
	{
		
	}

	float4 MoveDir;

	Gravity();
	//Move();

	return StateInfo();
}

StateInfo Player::Duck_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::Duck_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}

StateInfo Player::RockOn_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::RockOn_Update(StateInfo _state, float _DeltaTime)
{
	if (true == Key_Shoot_) // 쏘는중
	{
		//ShootRockOn();
	}
	else // 록온 자세만
	{

	}




	return StateInfo();
}

StateInfo Player::Bomb_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::Bomb_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}

StateInfo Player::Death_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::Death_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}

StateInfo Player::Hit_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::Hit_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}

StateInfo Player::Dash_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::Dash_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}
