#include "PreCompile.h"
#include "Mr_Wheezy.h"
#include "Stage_Mr_Wheezy.h"

void Mr_Wheezy::Intro_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDIce-Intro");
}
void Mr_Wheezy::Intro_Update( float _DeltaTime)
{
	if (true == AniEnd_Intro_)
	{
		State_.ChangeState("Idle");
		return;
	}

	 
}
void Mr_Wheezy::Intro_End_()
{
	AniEnd_Intro_ = false;
}

void Mr_Wheezy::Idle_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDIce-Idle");
}
void Mr_Wheezy::Idle_Update(float _DeltaTime)
{
	if (true == BattleState_.IsCurStateName("BattleState_Battle"))
	{
		if (Hp_ < 0)
		{
			State_.ChangeState("Defeat");
			return;
		}

		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 2.f)
		{
			State_.ChangeState("Attack");
			return;
		}
	}
	else if (true == BattleState_.IsCurStateName("BattleState_Dice"))
	{
		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 2.f)
		{
			State_.ChangeState("Clap");
			return;
		}
	}
}
void Mr_Wheezy::Idle_End_()
{
	TimeCheck_ = 0.f;
}

void Mr_Wheezy::Attack_Start() // 외부에서 특정 조건 만족시 실행
{
	CardClear();

	MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Birth");

	MonsterHitBox->On();
}
void Mr_Wheezy::Attack_Update( float _DeltaTime)
{
	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	if (true == AniEnd_Attack_Body_End_)
	{
		//CardClear();

		State_.ChangeState("Idle");
		return;
	}

	else
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
#endif // !_DEBUG

		if (true == Hand_.IsAttacking_)
		{
			TimeCheck_ += _DeltaTime;

			if (TimeCheck_ > 0.3f)
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

	}
	 
}
void Mr_Wheezy::Attack_End_()
{
	TimeCheck_ = 0.f;

	MonsterImageRenderer->GetTransform()->SetLocalScaling({ 1440.f, 750.0f, 1.0f });

	AniEnd_Attack_Body_Birth_ = false;
	AniEnd_Attack_Body_End_ = false;
	AniEnd_Attack_Hand_Birth_ = false;
}

void Mr_Wheezy::Defeat_Start()
{
	CardClear();

	TimeCheck_ = 0.f;
	MonsterHitBox->Off();

	MonsterImageRenderer->SetChangeAnimation("KDice-Defeat");

	Defeat_ = true;

	GetLevel<Stage_Mr_Wheezy>()->SetNextScene("WorldMap");

	GetLevel<Stage_Mr_Wheezy>()->Knockout();
}
void Mr_Wheezy::Defeat_Update( float _DeltaTime)
{
	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ >= 0.2f)
	{
		TimeCheck_ = 0.f;

		EffectDefeatRandom(250.f);
	}

	 
}
void Mr_Wheezy::Defeat_End_()
{
	TimeCheck_ = 0.f;
}

void Mr_Wheezy::Chop_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Chomp");
}
void Mr_Wheezy::Chop_Update( float _DeltaTime)
{
	 
}
void Mr_Wheezy::Chop_End_()
{
}

void Mr_Wheezy::Clap_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Clap");
}
void Mr_Wheezy::Clap_Update(float _DeltaTime)
{
#ifdef _DEBUG
	if (true == AniEnd_Clap_)
	{
		AniEnd_Clap_ = false;
		//State_.ChangeState("Idle");
		MonsterImageRenderer->SetChangeAnimation("KDIce-Idle");
		return;
	}
#endif // !_DEBUG

	if (true == AniEnd_Clap_Dice_)
	{
		//TODO : 담베, 토끼, 팽이발레
		//spawn dice
		//dice idle
		SpawnDice();

		AniEnd_Clap_Dice_ = false;
	}

	if (nullptr != PerryObjectDice_)
	{
		if (true == PerryObjectDice_->GetRoll())
		{
			int num = PerryObjectDice_->GetNumber();
			State_.ChangeState("Chop");
			return;
		}
	}


	//주사위 굴리기 끝나면



}
void Mr_Wheezy::Clap_End_()
{
}


void Mr_Wheezy::BattleState_Battle_Start()
{
	MonsterHitBox->On();
}
void Mr_Wheezy::BattleState_Battle_Update( float _DeltaTime)
{
	//주기적인 싸이클 속에서 공격, idle 반복 시킴

	 
}
void Mr_Wheezy::BattleState_Battle_End()
{
}

void Mr_Wheezy::BattleState_Dice_Start()
{

	MonsterHitBox->Off();
}
void Mr_Wheezy::BattleState_Dice_Update( float _DeltaTime)
{
	//IdleNextState_ = "Attack";
	//BattleState_.ChangeState("BattleState_Battle");
	//return;

	if (false == IsDiceTime_) 
	{
		BattleState_.ChangeState("BattleState_Battle");
		return;
	}

	 
}
void Mr_Wheezy::BattleState_Dice_End()
{
}
