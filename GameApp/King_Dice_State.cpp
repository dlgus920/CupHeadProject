#include "PreCompile.h"
#include "King_Dice.h"

void King_Dice::Intro_Start()
{
	MonsterHitBox->Off();
	MonsterHitBoxHand->Off();
}
StateInfo King_Dice::Intro_Update(StateInfo _StateInfo, float _DeltaTime)
{
	return StateInfo();
}
void King_Dice::Intro_End_()
{
}

void King_Dice::Idle_Start()
{

}
StateInfo King_Dice::Idle_Update(StateInfo _StateInfo, float _DeltaTime)
{
	return StateInfo();
}
void King_Dice::Idle_End_()
{
}

void King_Dice::Attack_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Birth");
	MonsterHitBox->On();
	MonsterHitBoxHand->On();
}
StateInfo King_Dice::Attack_Update(StateInfo _StateInfo, float _DeltaTime)
{
	if (true == Hand_.IsAttacking_)
	{
		// 카드 생성, 발사
	}


	return StateInfo();
}
void King_Dice::Attack_End_()
{
	MonsterHitBoxHand->Off();

	Hand_.HandOff();
}

void King_Dice::Defeat_Start()
{
	MonsterHitBox->Off();
	MonsterHitBoxHand->Off(); 
}
StateInfo King_Dice::Defeat_Update(StateInfo _StateInfo, float _DeltaTime)
{
	return StateInfo();
}
void King_Dice::Defeat_End_()
{
}

void King_Dice::Chop_Start()
{
}
StateInfo King_Dice::Chop_Update(StateInfo _StateInfo, float _DeltaTime)
{
	return StateInfo();
}
void King_Dice::Chop_End_()
{
}




void King_Dice::BattleState_Battle_Start()
{
}
StateInfo King_Dice::BattleState_Battle_Update(StateInfo _StateInfo, float _DeltaTime)
{
	return StateInfo();
}
void King_Dice::BattleState_Battle_End()
{
}

void King_Dice::BattleState_Dice_Start()
{
}
StateInfo King_Dice::BattleState_Dice_Update(StateInfo _StateInfo, float _DeltaTime)
{
	return StateInfo();
}
void King_Dice::BattleState_Dice_End()
{
}
