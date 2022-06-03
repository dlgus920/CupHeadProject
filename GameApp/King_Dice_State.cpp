#include "PreCompile.h"
#include "King_Dice.h"
#include "DicePaclace.h"
#include "PerryObjectDice.h"

void King_Dice::Intro_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Intro");
}
void King_Dice::Intro_Update( float _DeltaTime)
{
	if (true == AniEnd_Intro_)
	{
		State_.ChangeState("Idle");
		return;
	}
}
void King_Dice::Intro_End_()
{
	AniEnd_Intro_ = false;
}

void King_Dice::Idle_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Idle");
}
void King_Dice::Idle_Update(float _DeltaTime)
{
	if (true == BattleState_.IsCurStateName("BattleState_Battle"))
	{
		if (Hp_ < 0)
		{
			State_.ChangeState("Defeat");
			return;
		}

		TimeCheck_ += _DeltaTime;

		if (GameEngineSoundManager::GetInst().FindSoundChannel("DiceCardLoop")->IsPlay())
		{
			if (TimeCheck_ > 1.f)
			{
				GameEngineSoundManager::GetInst().FindSoundChannel("DiceCardLoop")->Stop();
			}
		}

		if (TimeCheck_ > 2.f)
		{
			if (true == Ani_Idle_Ready_)
			{
				State_.ChangeState("Attack");
				return;
			}
		}
	}

	else if (true == BattleState_.IsCurStateName("BattleState_Dice"))
	{
		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 2.f)
		{
			if (true == Ani_Idle_Ready_)
			{
				State_.ChangeState("Clap");
				return;
			}
		}
	}

	Ani_Idle_Ready_ = false;
}
void King_Dice::Idle_End_()
{
	TimeCheck_ = 0.f;
}

void King_Dice::Attack_Start() // 외부에서 특정 조건 만족시 실행
{
	if (true == FirstAttack_)
	{
		GetLevel<SceneBase>()->ReadyWALLOP_DICE();
		MonsterHitBox->On();
		FirstAttack_ = false;
	}

	CardClear();

	GameEngineSoundManager::GetInst().FindSoundChannel("DiceCardLoop")->Stop();

	MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Birth");

	MonsterHitBox->On();

	HandSwitching();

	Attack_bgm_on_ = false;

	GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "SFX_level_dice_palace_main_king_dice_attack_vox_01.wav",2);
}
void King_Dice::Attack_Update( float _DeltaTime)
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

		if (true == Hand_.IsAttacking_)
		{
			if (false == Attack_bgm_on_)
			{
				Attack_bgm_on_ = true;
				GameEngineSoundManager::GetInst().PlaySoundChannel("DiceCardLoop", "SFX_level_dice_palace_main_card_march_loop_01.wav", 1);
			}

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
void King_Dice::Attack_End_()
{
	TimeCheck_ = 0.f;
	CardCount_ = 0;

	Hand_.HandOff();

	MonsterImageRenderer->GetTransform()->SetLocalScaling({ 1440.f, 750.0f, 1.0f });

	AniEnd_Attack_Body_Birth_ = false;
	AniEnd_Attack_Body_End_ = false;
	AniEnd_Attack_Hand_Birth_ = false;
}

void King_Dice::Defeat_Start()
{
	GameEngineSoundManager::GetInst().FindSoundChannel("DiceCardLoop")->Stop();
	GameEngineSoundManager::GetInst().FindSoundChannel("Effect")->Stop();
	CardClear();

	TimeCheck_ = 0.f;
	MonsterHitBox->Off();
	Hand_.HandOff();

	MonsterImageRenderer->SetChangeAnimation("KDice-Defeat");

	Defeat_ = true;

	GetLevel<DicePaclace>()->Knockout();
}
void King_Dice::Defeat_Update( float _DeltaTime)
{
	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ >= 0.2f)
	{
		TimeCheck_ = 0.f;

		EffectDefeatRandom(250.f, GetTransform()->GetWorldPosition());
	}

	 
}
void King_Dice::Defeat_End_()
{
	TimeCheck_ = 0.f;
}

void King_Dice::Chop_Start()
{
	GameEngineSoundManager::GetInst().PlaySoundChannel("DiceChop","sfx_dice_palace_main_king_dice_eat_screen_01.wav");
	MonsterImageRenderer->SetChangeAnimation("KDice-Chomp");
	MonsterImageRenderer->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx02) });
}
void King_Dice::Chop_Update( float _DeltaTime)
{
}
void King_Dice::Chop_End_()
{
	MonsterImageRenderer->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back08) });
}

void King_Dice::Clap_Start()
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Clap");
}
void King_Dice::Clap_Update(float _DeltaTime)
{
	if (true == AniEnd_Clap_)
	{
		AniEnd_Clap_ = false;
		//State_.ChangeState("Idle");
		MonsterImageRenderer->SetChangeAnimation("KDice-Idle");
		return;
	}

	if (true == AniEnd_Clap_Dice_)
	{
		//TODO : 담베, 토끼, 팽이발레
		//spawn dice
		//dice idle
		GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "sfx_dice_palace_main_king_dice_reveal_2_02.wav");

		SpawnDice();

		AniEnd_Clap_Dice_ = false;
	}

	if (nullptr != PerryObjectDice_)
	{
		if (true == PerryObjectDice_->GetRoll())
		{
			TimeCheck_ += _DeltaTime;
			if (TimeCheck_ >= 2.f)
			{
				if (true == Ani_Idle_Ready_)
				{
					GetLevel<DicePaclace>()->SetPlusDiceNum(PerryObjectDice_->GetNumber());

					//TODO : 숫자를 받아왔으니, 이제 마커를 이동시키면 됨
					PerryObjectDice_->Death();
					PerryObjectDice_ = nullptr;

					State_.ChangeState("Chop");
					return;
				}
			}
		}
	}


	//주사위 굴리기 끝나면



}
void King_Dice::Clap_End_()
{
	TimeCheck_ = 0.f;
}


void King_Dice::BattleState_Battle_Start()
{
	//MonsterHitBox->On();
}
void King_Dice::BattleState_Battle_Update( float _DeltaTime)
{
	//주기적인 싸이클 속에서 공격, idle 반복 시킴

	 
}
void King_Dice::BattleState_Battle_End()
{
}

void King_Dice::BattleState_Dice_Start()
{
	MonsterHitBox->Off();
}
void King_Dice::BattleState_Dice_Update( float _DeltaTime)
{
	//IdleNextState_ = "Attack";
	//BattleState_.ChangeState("BattleState_Battle");
	//return;

	if (true == UserGame::StageInfo_.Dice_ClearStage_[4])
	{
		BattleState_.ChangeState("BattleState_Battle");
		return;
	}

	if (false == IsDiceTime_) 
	{
		BattleState_.ChangeState("BattleState_Battle");
		return;
	}

	 
}
void King_Dice::BattleState_Dice_End()
{
}
