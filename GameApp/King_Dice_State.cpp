#include "PreCompile.h"
#include "King_Dice.h"


void King_Dice::Intro_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDIce-Intro");
}
StateInfo King_Dice::Intro_Update(StateInfo _StateInfo, float _DeltaTime)
{
	if (true == AniEnd_Intro_)
	{
		return "Idle";
	}

	return StateInfo();
}
void King_Dice::Intro_End_()
{
	AniEnd_Intro_ = false;
}

void King_Dice::Idle_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDIce-Idle");
}
StateInfo King_Dice::Idle_Update(StateInfo _StateInfo, float _DeltaTime)
{
	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ > 2.f)
	{
		return IdleNextState_;
	}
	return StateInfo();
}
void King_Dice::Idle_End_()
{
	TimeCheck_ = 0.f;
}

void King_Dice::Attack_Start() // 외부에서 특정 조건 만족시 실행
{
	CardClear();

	MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Birth");

	HandSwitching();
}
StateInfo King_Dice::Attack_Update(StateInfo _StateInfo, float _DeltaTime)
{
#ifdef _DEBUG
	if (true == AniEnd_Attack_Body_Birth_)
	{
		MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Idle");

		Hand_.HandOn();
		Hand_.ImageRenderer->SetChangeAnimation("KDice-Attack-Hand-Birth");

		AniEnd_Attack_Body_Birth_ = false;
	}

	if (true == AniEnd_Attack_Hand_Birth_)
	{
		Hand_.ImageRenderer->SetChangeAnimation("KDice-Attack-Hand-Idle");

		Hand_.IsAttacking_ = true;

		AniEnd_Attack_Hand_Birth_ = false;
	}

	if (true == AniEnd_Attack_Body_End_)
	{
		return "Idle";
	}
#endif // !_DEBUG

	if (true == Hand_.IsAttacking_)
	{
		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 0.4f)
		{
			CardCount_++;

			if ((CardCount_ % 3) == 0)
			{
				SpawnParryCard();
			}
			else
			{
				SpawnCard();
			}

			if (CardCount_ > 10)
			{
				MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-End");
				Hand_.IsAttacking_ = false;
				Hand_.HandOff();
			}

			TimeCheck_ = 0.f;
		}
	}

	return StateInfo();
}
void King_Dice::Attack_End_()
{
	TimeCheck_ = 0.f;
	CardCount_ = 0;

	MonsterHitBoxHand->Off();
	Hand_.HandOff();

	MonsterImageRenderer->GetTransform()->SetLocalScaling({ 1440.f, 750.0f, 1.0f });

	AniEnd_Attack_Body_Birth_ = false;
	AniEnd_Attack_Body_End_ = false;
	AniEnd_Attack_Hand_Birth_ = false;
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
	MonsterHitBox->On();
	MonsterHitBoxHand->On();
}
StateInfo King_Dice::BattleState_Battle_Update(StateInfo _StateInfo, float _DeltaTime)
{
	//주기적인 싸이클 속에서 공격, idle 반복 시킴
	CardUpdate(_DeltaTime);

	return StateInfo();
}
void King_Dice::BattleState_Battle_End()
{
}

void King_Dice::BattleState_Dice_Start()
{
	IdleNextState_ = "Chop";

	MonsterHitBox->Off();
	MonsterHitBoxHand->Off();
}
StateInfo King_Dice::BattleState_Dice_Update(StateInfo _StateInfo, float _DeltaTime)
{
	IdleNextState_ = "Attack";
	return "BattleState_Battle";

	if (false == IsDiceTime_)
	{
		IdleNextState_ = "Attack";

		return "BattleState_Battle";
	}

	return StateInfo();
}
void King_Dice::BattleState_Dice_End()
{
}
