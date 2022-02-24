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

	//if (true == State_Hit_)
	//{
	//	if (Dir_ == Dir::Left)
	//	{
	//		//Hit_Left
	//	}
	//	else
	//	{
	//		//Hit_Right
	//	}
	//}
	//else if (true == Key_Bomb)
	//{
	//	if (Dir_ == Dir::Left)
	//	{
	//		//Bomb_Left
	//	}
	//	else
	//	{
	//		//Bomb_Right
	//	}
	//}
	//else if (true == Key_Jump_)
	//{
	//	if (Dir_ == Dir::Left)
	//	{
	//		//Jump_Left
	//	}
	//	else
	//	{
	//		//Jump_Right
	//	}
	//}
	//else if (true == Key_Dash_)
	//{
	//	if (Dir_ == Dir::Left)
	//	{
	//		//Dash_Left
	//	}
	//	else
	//	{
	//		//Dash_Right
	//	}
	//}
	//else if (true == Key_RockOn_)
	//{
	//	if (true == Key_Shoot_) // 쏘는중
	//	{
	//		if (Key_Up_)
	//		{
	//			if (Key_Left_)
	//			{
	//				//RockOn_UpLeft_Shoot
	//			}
	//			else if (Key_Right_)
	//			{
	//				//RockOn_UpRight_Shoot
	//			}
	//			else
	//			{
	//				if (Dir_ == Dir::Left)
	//				{
	//					//RockOn_LeftUp_Shoot
	//				}
	//				else
	//				{
	//					//RockOn_RightUp_Shoot
	//				}
	//			}
	//		}
	//		else if(Key_Down_)
	//		{
	//			if (Key_Left_)
	//			{
	//				//RockOn_DownLeft_Shoot
	//			}
	//			else if (Key_Right_)
	//			{
	//				//RockOn_DownRight_Shoot
	//			}
	//			else
	//			{
	//				if (Dir_ == Dir::Left)
	//				{
	//					//RockOn_LeftDown_Shoot
	//				}
	//				else
	//				{
	//					//RockOn_RightDown_Shoot
	//				}
	//			}
	//		}
	//	}
	//	else 
	//	{
	//		if (Key_Up_)
	//		{
	//			if (Key_Left_)
	//			{
	//				//RockOn_UpLeft_
	//			}
	//			else if (Key_Right_)
	//			{
	//				//RockOn_UpRight_
	//			}
	//			else
	//			{
	//				if (Dir_ == Dir::Left)
	//				{
	//					//RockOn_LeftUp_
	//				}
	//				else
	//				{
	//					//RockOn_RightUp_
	//				}
	//			}
	//		}
	//		else if (Key_Down_)
	//		{
	//			if (Key_Left_)
	//			{
	//				//RockOn_DownLeft_
	//			}
	//			else if (Key_Right_)
	//			{
	//				//RockOn_DownRight_
	//			}
	//			else
	//			{
	//				if (Dir_ == Dir::Left)
	//				{
	//					//RockOn_LeftDown_
	//				}
	//				else
	//				{
	//					//RockOn_RightDown_
	//				}
	//			}
	//		}
	//	}
	//}
	//else if (true == Key_Down_)
	//{
	//	if (true == Key_Shoot_) // 쏘는중
	//	{		
	//		if (Dir_ == Dir::Left)
	//		{
	//			//Duck_Left_Shoot
	//		}
	//		else
	//		{
	//			//Duck_Right_Shoot
	//		}
	//	}
	//	else
	//	{
	//		if (Dir_ == Dir::Left)
	//		{
	//			//Duck_Left_
	//		}
	//		else
	//		{
	//			//Duck_Right_
	//		}
	//	}
	//}
	//else if (true == Key_Right_)
	//{
	//	if (true == Key_Shoot_)
	//	{
	//		//Walk_Right_Shoot
	//	}
	//	else
	//	{
	//		//Walk_Right_
	//	}
	//}
	//else if (true == Key_Left_)
	//{
	//	if (true == Key_Shoot_)
	//	{
	//		//Walk_Left_Shoot
	//	}
	//	else
	//	{
	//		//Walk_Left_
	//	}
	//}
	//else if (true == Key_Shoot_)
	//{
	//	if (Dir_ == Dir::Left)
	//	{
	//		//Idle_Left_Shoot 
	//	}
	//	else
	//	{
	//		//Idle_Right_Shoot
	//	}
	//}

	return StateInfo();
}

StateInfo Player::Walk_Start(StateInfo _state)
{
	// 각기 다른 에니메이션 재생

	return StateInfo();
}
StateInfo Player::Walk_Update(StateInfo _state, float _DeltaTime)
{
	if (true == Key_Bomb)
	{
		return "Bomb";
	}
	else if (true == Key_Jump_)
	{
		return "Jump";
	}
	else if (true == Key_Dash_)
	{
		return "Dash";
	}
	else if (true == Key_RockOn_)
	{
		return "RockOn";
	}

	if (true == State_Ground)
	{
		if (!(Key_Up_ && Key_Down_ && Key_Right_ && Key_Left_))
		{
			return "Idle";
		}
	}

	if (true == Key_Shoot_) // 쏘는중
	{
		if (Key_Up_)
		{
			if (Key_Left_)
			{
				// 업 레프트
			}
			else if (Key_Right_)
			{
				// 업 라이트
			}
			else
			{
				if (Dir_ == Dir::Left)
				{
					//왼쪽 업
				}
				else
				{
					//오른쪽 업
				}
			}

			return "Idle";
		}
		else if (Key_Right_) //이동중 or 록온중
		{

		}
		else if (Key_Left_)
		{

		}
	}
	else
	{

	}

	if(Key_Right_)
	{
		MoveDir_ = { 0.f,1.f,0.f };
	}
	else if (Key_Left_)
	{
		MoveDir_ = { 0.f,1.f,0.f };
	}

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
		ShootJump();
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
	Move();

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
		ShootRockOn();
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
