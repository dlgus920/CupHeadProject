#include "PreCompile.h"
#include "Hopus_pocus.h"
#include "Effect.h"

#include "Stage_Hopus_pocus.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineSoundManager.h>
#include <GameEngine/GameEngineSoundPlayer.h>

void Hopus_pocus::Intro_Start()
{
	GameEngineSoundManager::GetInst().FindSoundChannel("Effect")->SetVolume(1.f);

	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_Pocus-Intro");

	GameEngineSoundManager::GetInst().PlaySoundChannel("BGM", "MUS_CasinoCriminals_02.wav");
	GameEngineSoundManager::GetInst().FindSoundChannel("Intro")->PlayLevelOverLap("sfx_dice_palace_rabbit_intro_continue_02.wav");
	//GameEngineSoundManager::GetInst().FindSoundChannel("Intro")->SetVolume(0.7f);

}
void Hopus_pocus::Intro_Update( float _DeltaTime)
{
	if (true == AniEnd_Intro_)
	{
		State_.ChangeState("Idle");
		return;
	}
}
void Hopus_pocus::Intro_End()
{
	AniEnd_Intro_ = false;
}

void Hopus_pocus::Idle_Start()
{
	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_Pocus-Idle");

	GameEngineRandom rand;

	int randcount = rand.RandomInt(0, 2);

	if(randcount ==0)
		GameEngineSoundManager::GetInst().PlaySoundChannel("Hopus_idle", "sfx_level_dice_palace_rabbit_idle_twirl_loop_01.wav");
	else if(randcount ==1)
		GameEngineSoundManager::GetInst().PlaySoundChannel("Hopus_idle", "sfx_level_dice_palace_rabbit_idle_twirl_loop_02.wav");
	else
		GameEngineSoundManager::GetInst().PlaySoundChannel("Hopus_idle", "sfx_level_dice_palace_rabbit_idle_twirl_loop_03.wav");

	GameEngineSoundManager::GetInst().FindSoundChannel("Hopus_idle")->SetVolume(0.3f);	
}
void Hopus_pocus::Idle_Update(float _DeltaTime)
{
	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	if (false == GameEngineSoundManager::GetInst().FindSoundChannel("Hopus_idle")->IsPlay())
	{
		GameEngineRandom rand;

		int randcount = rand.RandomInt(0, 2);

		if (randcount == 0)
			GameEngineSoundManager::GetInst().PlaySoundChannel("Hopus_idle", "sfx_level_dice_palace_rabbit_idle_twirl_loop_01.wav");
		else if (randcount == 1)
			GameEngineSoundManager::GetInst().PlaySoundChannel("Hopus_idle", "sfx_level_dice_palace_rabbit_idle_twirl_loop_02.wav");
		else
			GameEngineSoundManager::GetInst().PlaySoundChannel("Hopus_idle", "sfx_level_dice_palace_rabbit_idle_twirl_loop_03.wav");
		GameEngineSoundManager::GetInst().FindSoundChannel("Hopus_idle")->SetVolume(0.3f);
	}

	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ > 3.f)
	{
		GameEngineSoundManager::GetInst().FindSoundChannel("Hopus_idle")->Stop();
		//if (FireCount_ == 3)
		//{
		//	FireCount_ = 0;
		//	State_.ChangeState("Telleport");
		//	return;
		//}

		State_.ChangeState("Attack");


		return;
	}
}
void Hopus_pocus::Idle_End()
{
	TimeCheck_ = 0.f;
}

void Hopus_pocus::Attack_Start() // 외부에서 특정 조건 만족시 실행
{
	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_Pocus-Attack");

	GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", "sfx_dice_palace_rabbit_attack_start_01.wav");

	if (true == Houpus_AIPattern_)
	{
		Houpus_AIPattern_ = false;
	}
	else
	{
		Houpus_AIPattern_ = true;
	}
	FireReady();
}
void Hopus_pocus::Attack_Update( float _DeltaTime)
{

	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	if (true == AniEnd_Attack_)
	{
		GameEngineSoundManager::GetInst().FindSoundChannel("Hopus_Attack")->Stop();

		GameEngineRandom rand;

		int randint = rand.RandomInt(1, 4);

		std::string str = "sfx_dice_palace_rabbit_attack_end_0";
		std::string strnum = std::to_string(randint);
		str = str + strnum + ".wav";

		GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", str);


		randint = rand.RandomInt(1, 7);

		str = "sfx_level_dice_palace_rabbit_idle_vox_0";
		strnum = std::to_string(randint);
		str = str + strnum + ".wav";

		GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", str);
		
		AniEnd_Attack_ = false;
	}

	if (true == AniEnd_Attack_End_)
	{
		Fire();

		State_.ChangeState("Idle");
		return;
	}	

#ifdef _DEBUG
	else
	{
	}
#endif // !_DEBUG
	 
}
void Hopus_pocus::Attack_End()
{
	AniEnd_Attack_ = false;
	AniEnd_Attack_End_ = false;

	TimeCheck_ = 0.f;
}

void Hopus_pocus::Defeat_Start()
{
	TimeCheck_ = 0.f;
	MonsterHitBox->Off();
	MonsterBox->Off();

	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_Pocus-Death");

	Defeat_ = true;

	GetLevel<Stage_Hopus_pocus>()->Knockout();
}
void Hopus_pocus::Defeat_Update(float _DeltaTime)
{
	//if (true == AniEnd_Death_Intro_)
	//{
	//	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_pocus-Death-Idle");
	//	AniEnd_Death_Intro_ = false;
	//}

	TimeCheck_ += _DeltaTime;

	if (false == GameEngineSoundManager::GetInst().FindSoundChannel("Hopus_Deffeat")->IsPlay())
	{
		GameEngineRandom rand;
		int randint = rand.RandomInt(1, 4);

		std::string str = "sfx_dice_palace_rabbit_death_0";
		std::string strnum = std::to_string(randint);

		str = str + strnum + ".wav";
		GameEngineSoundManager::GetInst().PlaySoundChannel("Hopus_Deffeat", str);
	}


	if (TimeCheck_ >= 0.2f)
	{
		TimeCheck_ = 0.f;

		EffectDefeatRandom(250.f, MonsterBox->GetTransform()->GetWorldPosition());
	} 


}
void Hopus_pocus::Defeat_End()
{
	//AniEnd_Death_Intro_ = false;
	Defeat_ = false;
	TimeCheck_ = 0.f;
}
