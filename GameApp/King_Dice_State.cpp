#include "PreCompile.h"
#include "King_Dice.h"

void King_Dice::Intro_Start()
{
	MonsterHitBox->Off();
	MonsterHitBoxHand->Off();
}
StateInfo King_Dice::Intro_Update(StateInfo _StateInfo, float _DeltaTime)
{
#ifdef _DEBUG
	if (true == MonsterImageRenderer->GetCurAnimation_End("KDIce-Intro"))
	{
		return "Idle";
	}
#endif // _DEBUG

	return StateInfo();
}
void King_Dice::Intro_End_()
{
}

void King_Dice::Idle_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDIce-Idle");
}
StateInfo King_Dice::Idle_Update(StateInfo _StateInfo, float _DeltaTime)
{
	return StateInfo();
}
void King_Dice::Idle_End_()
{
}

void King_Dice::Attack_Start() // 외부에서 특정 조건 만족시 실행
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Birth");
	MonsterHitBox->On();
	MonsterHitBoxHand->On();
}
StateInfo King_Dice::Attack_Update(StateInfo _StateInfo, float _DeltaTime)
{
#ifdef _DEBUG
	//if (true == MonsterImageRenderer->GetCurAnimation_End("KDice-Attack-Body-Birth"))
	if (true == MonsterImageRenderer->GetCurAnimation_End())
	{
		MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Idle");
		Hand_.HandIdle();
		Hand_.HandOn();
	}
#endif // _DEBUG

	if (true == Hand_.HandIsAttacking())
	{
		//TimeCheck_ += _DeltaTime;
		//if (TimeCheck_ > 0.5f)
		//{
		//	// 카드 생성, 발사
		//	CardCount_++;
		//	if (CardCount_ > 10)
		//	{
		//		MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-End");
		//		Hand_.HandOff();
		//	}
		//}
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
