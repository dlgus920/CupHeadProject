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
	// ���� �ٸ� ���ϸ��̼� ���

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
	//TODO : �����ϰ� �ö󰥶� ���������� flag �Ͽ� �ϴ�, ��� �ø����� Ű�� ����.
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
	if (true) // ���� ������
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
	if (true) // ���� ������
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

	if (true) // ���� ������
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
	if (true) // ���� ������
	{
		return "Idle";
	}
	else
	{
		return StateInfo();
	}
}
