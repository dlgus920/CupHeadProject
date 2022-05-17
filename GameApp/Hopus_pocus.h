#pragma once
#include "Monster.h"
#include <GameEngineBase/GameEngineFSM.h>

class GameEngineCollision;
class GameEngineImageRenderer;
class Hopus_pocus : public Monster
{
public:
	Hopus_pocus(); 
	~Hopus_pocus(); 

	Hopus_pocus(const Hopus_pocus& _other) = delete; 
	Hopus_pocus(Hopus_pocus&& _other) = delete; 
	Hopus_pocus& operator=(const Hopus_pocus& _other) = delete; 
	Hopus_pocus& operator=(const Hopus_pocus&& _other) = delete; 
private:
	GameEngineFSM<Hopus_pocus> State_;

	GameEngineCollision* MonsterHitBox;
	GameEngineCollision* MonsterBox;

	GameEngineImageRenderer* Hopus_pocusImageRenderer_;

	bool Defeat_;

	float TimeCheck_;

	bool AniEnd_Idle_;
	bool AniEnd_Intro_;
	bool AniEnd_Attack_;
	bool AniEnd_Attack_End_;

#ifdef _DEBUG
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

private:	

	void SpawnSmokeFx();

	void Firefire();


private:

	void AniEnd_Intro()
	{
		Hopus_pocusImageRenderer_->GetTransform()->SetLocalScaling(float4{640.f,740.f});
		Hopus_pocusImageRenderer_->GetTransform()->SetWorldMove(float4{-90.f,0.f});
	}






#ifdef _DEBUG

	void AniEnd_Intro()
	{
		AniEnd_Intro_ = true;
	}
	void AniEnd_Attack()
	{
		AniEnd_Attack_ = true;
	}
	void AniEnd_Attack_End()
	{
		AniEnd_Attack_End_ = true;
	}
	void AniEnd_Idle()
	{
		AniEnd_Idle_ = true;
	}
#endif // _DEBUG

	void AniStateClear()
	{
		AniEnd_Intro_ = false;
		AniEnd_Attack_ = false;
		AniEnd_Attack_End_ = false;
		AniEnd_Idle_ = false;
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

