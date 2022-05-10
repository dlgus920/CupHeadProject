#pragma once
#include "Monster.h"
#include <GameEngineBase/GameEngineFSM.h>

class GameEngineCollision;
class GameEngineImageRenderer;
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
	GameEngineCollision* MonsterBox;

	GameEngineImageRenderer* WheezyImageRenderer_Left_;
	GameEngineImageRenderer* WheezyImageRenderer_Right_;

	GameEngineImageRenderer* Cur_WheezyImageRenderer_;

	GameEngineImageRenderer* AshImageRenderer_Left_Front;
	GameEngineImageRenderer* AshImageRenderer_Right_Front;

	GameEngineImageRenderer* AshImageRenderer_Left_Back;
	GameEngineImageRenderer* AshImageRenderer_Right_Back;

	bool PossitionLeft_;
	bool Defeat_;
	float TimeCheck_;

	int FireCount_;

	bool AniEnd_Intro_;
	bool AniEnd_Attack_;
	bool AniEnd_TellePort_In_;
	bool AniEnd_TellePort_Out_;
	bool AniEnd_TellePort_HB_;
	bool AniEnd_Death_Intro_;
	bool AniEnd_Attack_End_;
#ifdef _DEBUG
#endif // _DEBUG

private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;

public:


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
	void ChangeCurRenderer();
	void ChangeAshImageRenderer();
	void MoveHitBox();

	void SpawnSmokeFx();

private:
	void SwapPosition()
	{
		if (true == PossitionLeft_)
		{
			PossitionLeft_ = false;
		}
		else
		{
			PossitionLeft_ = true;
		}
	}

	void Firefire();

#ifdef _DEBUG
	void AniEnd_TellePort_HB_On()
	{
		AniEnd_TellePort_HB_ = true;
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

