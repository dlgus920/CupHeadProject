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
	GameEngineFSM State_;

	GameEngineCollision* MonsterHitBox;
	GameEngineCollision* MonsterBox;

	GameEngineImageRenderer* Hopus_pocusImageRenderer_;

	class Hopus_Bullet* Hopus_Bullet_;
	class Hopus_Trumps* Hopus_Trumps_;

	bool Defeat_;

	float TimeCheck_;

	bool Houpus_AIPattern_;

	bool AniEnd_Idle_;
	bool AniEnd_Intro_;
	bool AniEnd_Attack_;
	bool AniEnd_Attack_End_;

private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Attack_Start();
	void Attack_Update(float _DeltaTime);
	void Attack_End();

	void Defeat_Start();
	void Defeat_Update(float _DeltaTime);
	void Defeat_End();

private:	

	void SpawnSmokeFx();

	void Fire();
	void FireReady();


private:

	void AniEnd_Intro();

	void AniEnd_Attack_Sound();

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

	void AniStateClear()
	{
		AniEnd_Intro_ = false;
		AniEnd_Attack_ = false;
		AniEnd_Attack_End_ = false;
		AniEnd_Idle_ = false;
	}
};

