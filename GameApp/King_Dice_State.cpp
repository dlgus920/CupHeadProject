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
	MonsterHitBox->On();
	MonsterHitBoxHand->On();
}

StateInfo King_Dice::Attack_Update(StateInfo _StateInfo, float _DeltaTime)
{
	return StateInfo();
}

void King_Dice::Attack_End_()
{
	MonsterHitBoxHand->Off();
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
