#include "PreCompile.h"
#include "Player.h"
//#include <GameEngine/GameEngineImageRenderer.h>


StateInfo Player::Idle_Start(StateInfo _state)
{
	return StateInfo();
}
StateInfo Player::Idle_Update(StateInfo _state, float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	return StateInfo();
}

StateInfo Player::Walk_Start(StateInfo _state)
{
	// 각기 다른 에니메이션 재생

	return StateInfo();
}
StateInfo Player::Walk_Update(StateInfo _state, float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	return StateInfo();
}

StateInfo Player::Jump_Start(StateInfo _state)
{
	return StateInfo();
}
StateInfo Player::Jump_Update(StateInfo _state, float _DeltaTime)
{
	//TODO : 점프하고 올라갈때 내려갈때를 flag 하여 하단, 상단 컬리전을 키고 끈다.
	StateUpdate(_DeltaTime);

	return StateInfo();
}

StateInfo Player::Duck_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::Duck_Update(StateInfo _state, float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	return StateInfo();
}

StateInfo Player::RockOn_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::RockOn_Update(StateInfo _state, float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	return StateInfo();
}

StateInfo Player::Bomb_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::Bomb_Update(StateInfo _state, float _DeltaTime)
{
	if (true) // 조건 충족시
	{
		if (true == ColState_Ground)
		{
			return "Idle";
		}
		else
		{
			return "Jump";
		}
	}
	else
	{
		return StateInfo();
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
	State_Update_ = false;
	return StateInfo();
}

StateInfo Player::Hit_Update(StateInfo _state, float _DeltaTime)
{
	//StateUpdate(_DeltaTime);

	if (true) // 조건 충족시
	{
		State_Update_ = true;
		return "Idle";
	}
	else
	{
		return StateInfo();
	}
}

StateInfo Player::Dash_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo Player::Dash_Update(StateInfo _state, float _DeltaTime)
{
	if (true) // 조건 충족시
	{
		return "Idle";
	}
	else
	{
		return StateInfo();
	}
}
