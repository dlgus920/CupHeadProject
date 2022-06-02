#include "PreCompile.h"
#include "Mr_Wheezy.h"
#include "Effect.h"

#include "Stage_Mr_Wheezy.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineSoundManager.h>
#include <GameEngine/GameEngineSoundPlayer.h>

void Mr_Wheezy::Intro_Start()
{
	//GameEngineSoundManager::GetInst().PlaySoundChannel("Effect","sfx_dice_palace_cigar_intro_start_loop_01.wav");
	GameEngineSoundPlayer* intro = GameEngineSoundManager::GetInst().FindSoundChannel("Intro");
	intro->PlayLevelOverLap("sfx_dice_palace_cigar_intro_start_loop_01.wav");
	intro->SetVolume(0.5f);

	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Intro_Idle");
}
void Mr_Wheezy::Intro_Update( float _DeltaTime)
{
	TimeCheck_ += _DeltaTime;
	if (TimeCheck_ >= 1.f)
	{
		Lighter_->SetChangeAnimation("Intro_Hand_end");
		Fire_->SetChangeAnimation("Intro_Flame_end");
		Lighter_->Off();
		Fire_->Off();

		WheezyImageRenderer_Right_->SetChangeAnimation("Mr_Wheezy-Intro_End");
	}


	if (true == AniEnd_Intro_)
	{
		GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "sfx_dice_palace_cigar_intro_end_01.wav");

		State_.ChangeState("Idle");
		return;
	}
}
void Mr_Wheezy::Intro_End_()
{
	GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "cigar_vox_intro.wav");

	AniEnd_Intro_ = false;
}

void Mr_Wheezy::Idle_Start()
{
	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Idle");
}
void Mr_Wheezy::Idle_Update(float _DeltaTime)
{
	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ > 2.5f)
	{
		if (FireCount_ == 3)
		{
			FireCount_ = 0;
			State_.ChangeState("Telleport");
			return;
		}

		State_.ChangeState("Attack");
		return;
	}
}
void Mr_Wheezy::Idle_End_()
{
	TimeCheck_ = 0.f;
}

void Mr_Wheezy::Attack_Start() // 외부에서 특정 조건 만족시 실행
{
	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Attack");

	GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "sfx_dice_palace_cigar_attack_01.wav");
}
void Mr_Wheezy::Attack_Update( float _DeltaTime)
{
	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	if (true == AniEnd_Attack_)
	{
		Firefire();
		FireCount_++;

		AniEnd_Attack_ = false;
	}

	if (true == AniEnd_Attack_End_)
	{
		State_.ChangeState("Idle");
		return;
	}	

#ifdef _DEBUG
	else
	{
	}
#endif // !_DEBUG
	 
}
void Mr_Wheezy::Attack_End_()
{
	AniEnd_Attack_ = false;
	AniEnd_Attack_End_ = false;

	TimeCheck_ = 0.f;
}

void Mr_Wheezy::Defeat_Start()
{
	TimeCheck_ = 0.f;
	MonsterHitBox->Off();
	MonsterBox->Off();

	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Death-Intro");

	Defeat_ = true;

	GameEngineSoundManager::GetInst().FindSoundChannel("BGM")->Stop();

	GetLevel<Stage_Mr_Wheezy>()->Knockout();


}
void Mr_Wheezy::Defeat_Update(float _DeltaTime)
{
	if (true == AniEnd_Death_Intro_)
	{
		Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Death-Idle");
		AniEnd_Death_Intro_ = false;
	}

	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ >= 0.2f)
	{
		TimeCheck_ = 0.f;

		float4 pos = Cur_WheezyImageRenderer_->GetTransform()->GetWorldPosition();
		pos.y - 450.f;

		EffectDefeatRandom(250.f, pos);
	} 
}
void Mr_Wheezy::Defeat_End_()
{
	AniEnd_Death_Intro_ = false;
	Defeat_ = false;
	TimeCheck_ = 0.f;
}

void Mr_Wheezy::Telleport_Start()
{
	GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "sfx_dice_palace_cigar_teleport_01.wav");

	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-TellePort-In");
}
void Mr_Wheezy::Telleport_Update(float _DeltaTime)
{

	if (true == AniEnd_TellePort_HB_)
	{
		if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Right_)
		{
			Effect* Effectfx = GetLevel()->CreateActor<Effect>();
			Effectfx->EffectAnimationActor("Smoke_FX_Front.png", "Smoke_FX", float4{ 552.f,228.f }, 0, 11, 0.04f, false);
			Effectfx->GetTransform()->SetWorldPosition(float4{ 1040.f, -240.f, static_cast<float>(ZOrder::Z00Fx02) });

		}
		else if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Left_)
		{
			Effect* Effectfx = GetLevel()->CreateActor<Effect>();
			Effectfx->EffectAnimationActor("Smoke_FX_Front.png", "Smoke_FX", float4{ 552.f,228.f }, 0, 11, 0.04f, false);
			Effectfx->GetTransform()->SetWorldPosition(float4{ 240.f, -240.f, static_cast<float>(ZOrder::Z00Fx02) });
		}

		MonsterHitBox->Off();
		MonsterBox->Off();

		AniEnd_TellePort_HB_ = false;
	}

	if (true == AniEnd_TellePort_In_)
	{
		if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Right_)
		{
			Effect* Effectfx = GetLevel()->CreateActor<Effect>();
			Effectfx->EffectAnimationActor("Smoke_FX_Front.png", "Smoke_FX", float4{ 552.f,228.f }, 0, 11, 0.04f, false);
			Effectfx->GetTransform()->SetWorldPosition(float4{ 1040.f, -300.f, static_cast<float>(ZOrder::Z00Fx02) });

			WheezyImageRenderer_Right_->SetChangeAnimation("Mr_Wheezy-TellePort-Out");
			WheezyImageRenderer_Right_->AnimationStop();

			WheezyImageRenderer_Left_->AnimationPlay();
			PossitionLeft_ = false;
			AniEnd_TellePort_In_ = false;
		}
		else if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Left_)
		{
			Effect* Effectfx = GetLevel()->CreateActor<Effect>();
			Effectfx->EffectAnimationActor("Smoke_FX_Front.png", "Smoke_FX", float4{ 552.f,228.f }, 0, 11, 0.04f, false);
			Effectfx->GetTransform()->SetWorldPosition(float4{ 240.f, -300.f, static_cast<float>(ZOrder::Z00Fx02) });

			WheezyImageRenderer_Left_->SetChangeAnimation("Mr_Wheezy-TellePort-Out");
			WheezyImageRenderer_Left_->AnimationStop();

			WheezyImageRenderer_Right_->AnimationPlay();
			PossitionLeft_ = true;
			AniEnd_TellePort_In_ = false;
		}
	}

	if (false == AniEnd_TellePort_In_)
	{
		if (true == AniEnd_TellePort_Out_)
		{
			MonsterHitBox->On();
			MonsterBox->On();

			GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "sfx_dice_palace_cigar_teleport_end_01.wav");

			if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Right_)
			{
				MonsterHitBox->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back05)));
				MonsterBox->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back05)));
				Cur_WheezyImageRenderer_ = WheezyImageRenderer_Left_;
			}
			else if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Left_)
			{
				MonsterHitBox->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back05)));
				MonsterBox->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back05)));
				Cur_WheezyImageRenderer_ = WheezyImageRenderer_Right_;
			}

			GameEngineRandom rand;

			int randint =  rand.RandomInt(0, 1);

			if (randint == 0)
			{
				GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "cigar_vox_warning_01.wav");
			}
			else
			{
				GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "cigar_vox_warning_03.wav");
			}

			AniEnd_TellePort_Out_ = false;
			State_.ChangeState("Idle");
			return;
		}
	}
}
void Mr_Wheezy::Telleport_End_()
{
	AniEnd_TellePort_In_ = false;
	AniEnd_TellePort_HB_ = false;
}
