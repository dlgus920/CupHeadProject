#pragma once
#include "Monster.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineFSM.h>

class Mr_Wheezy : public Monster
{
public:
	Mr_Wheezy(); 
	~Mr_Wheezy(); 

	Mr_Wheezy(const Mr_Wheezy& _other) = delete; 
	Mr_Wheezy(Mr_Wheezy&& _other) = delete; 
	Mr_Wheezy& operator=(const Mr_Wheezy& _other) = delete; 
	Mr_Wheezy& operator=(const Mr_Wheezy&& _other) = delete; 

private:
	GameEngineFSM<Mr_Wheezy> State_;

	GameEngineCollision* MonsterHitBox;
	GameEngineImageRenderer* MonsterImageRenderer;

	bool Defeat_;
	float TimeCheck_;

#ifdef _DEBUG
	bool AniEnd_Intro_;
	bool AniEnd_Attack_;
	bool AniEnd_TellePort_In_;
	bool AniEnd_TellePort_HB_;
	bool AniEnd_TellePort_Out_;
	bool AniEnd_Death_Intro_;
	bool AniEnd_Attack_End_;
#endif // _DEBUG

private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End_();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End_();

	void Attack_Start();
	void Attack_Update(float _DeltaTime);
	void Attack_End_();

	void Defeat_Start();
	void Defeat_Update(float _DeltaTime);
	void Defeat_End_();

	void Telleport_Start();
	void Telleport_Update(float _DeltaTime);
	void Telleport_End_();

private:	

	void SpawnSmokeFx();

private:
	
#ifdef _DEBUG
	void AniEnd_TellePort_HB_On()
	{
		AniEnd_TellePort_HB_ = true;
	}
	void AniEnd_TellePort_HB_Off()
	{
		AniEnd_TellePort_HB_ = false;
	}

	void AniEnd_Intro()
	{
		AniEnd_Intro_ = true;
	}
	void AniEnd_TellePort_In()
	{
		AniEnd_TellePort_In_ = true;
	}
	void AniEnd_TellePort_Out()
	{
		AniEnd_TellePort_Out_ = true;
	}
	void AniEnd_Death_Intro()
	{
		AniEnd_Death_Intro_ = true;
	}
	void AniEnd_Attack()
	{
		AniEnd_Attack_ = true;
	}
	void AniEnd_Attack_End()
	{
		AniEnd_Attack_End_ = true;
	}
#endif // _DEBUG

	void AniStateClear()
	{
		AniEnd_Intro_ = false;
		AniEnd_Attack_ = false;
		AniEnd_TellePort_In_ = false;
		AniEnd_TellePort_Out_ = false;
		AniEnd_Death_Intro_ = false;
		AniEnd_Attack_End_ = false;
	}

#ifndef _DEBUG
	void AniEnd_Intro()
	{
		AniEnd_Intro_ = true;
	}
	void AniEnd_TellePort_In()
	{
		AniEnd_TellePort_In_ = true;
	}
	void AniEnd_TellePort_Out()
	{
		AniEnd_TellePort_Out_ = true;
	}
	void AniEnd_Death_Intro()
	{
		AniEnd_Death_Intro_ = true;
	}
	void AniEnd_Attack()
	{
		AniEnd_Attack_ = true;
	}
#endif // _DEBUG



};

