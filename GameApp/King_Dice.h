#pragma once
#include "Monster.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineFSM.h>

class Dice_Card;

class King_Dice : public Monster
{
public:
	King_Dice(); // default constructer 디폴트 생성자
	~King_Dice(); // default destructer 디폴트 소멸자

	King_Dice(const King_Dice& _other) = delete; // default Copy constructer 디폴트 복사생성자
	King_Dice(King_Dice&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	King_Dice& operator=(const King_Dice& _other) = delete; // default Copy operator 디폴트 대입 연산자
	King_Dice& operator=(const King_Dice&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	GameEngineFSM<King_Dice> State_;
	GameEngineFSM<King_Dice> BattleState_;

	GameEngineCollision* MonsterHitBox;
	//GameEngineCollision* MonsterHitBoxHand;

	GameEngineImageRenderer* MonsterImageRenderer;

	class PerryObjectDice* PerryObjectDice_;

	bool Defeat_;

	int CardCount_;
	float TimeCheck_;

	bool IsDiceTime_;

	bool Ani_Idle_Ready_;

#ifdef _DEBUG
	bool AniEnd_Intro_;
	bool AniEnd_Attack_Body_Birth_;
	bool AniEnd_Attack_Body_End_;

	bool AniEnd_Attack_Hand_Birth_;

#endif // _DEBUG
	bool AniEnd_Clap_Dice_;
	bool AniEnd_Clap_;


	enum class Hand_Dir
	{
		Right,
		Left
	};

	struct Hand
	{
		Hand();
		~Hand();

		GameEngineCollision* Collision;
		GameEngineImageRenderer* ImageRenderer;
		Hand_Dir Hand_Dir_;
		bool IsAttacking_;

		void HandSetHorizenInvertTransform();
		void HandOff();
		void HandOn();
		void HandIdle();
		void HandEnd();
		void HandBirth();
	};

	std::vector<Dice_Card*> Cardvector_;
	Hand Hand_;

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

	void Chop_Start();
	void Chop_Update(float _DeltaTime);
	void Chop_End_();

	void Clap_Start();
	void Clap_Update(float _DeltaTime);
	void Clap_End_();

	void BattleState_Battle_Start();
	void BattleState_Battle_Update(float _DeltaTime);
	void BattleState_Battle_End();

	void BattleState_Dice_Start();
	void BattleState_Dice_Update(float _DeltaTime);
	void BattleState_Dice_End();

public:
	void Intro();
	void Idle();
	void Attack();


private:	
	void HandSwitching();
	void HandRight();
	void HandLeft();

	void HandBirth();
	void HandIdle();

	void SpawnCard();
	void SpawnParryCard();
	void CardClear();

	void SpawnDice();

	//void EffectDefeat(float4 _Pos);
	//void EffectDefeatRandom(float _Radius);

private:

	void AniEnd_Clap_Dice()
	{
		AniEnd_Clap_Dice_ = true;
	}

	void Ani_Idle_Ready()
	{
		Ani_Idle_Ready_ = true;
	}

#ifdef _DEBUG
	void AniEnd_Intro()
	{
		AniEnd_Intro_ = true;
	}
	void AniEnd_Attack_Body_Birth()
	{
		AniEnd_Attack_Body_Birth_ = true;
	}
	void AniEnd_Attack_Body_End()
	{
		AniEnd_Attack_Body_End_ = true;
	}
	void AniEnd_Attack_Hand_Birth()
	{
		AniEnd_Attack_Hand_Birth_ = true;
	}	
	void AniEnd_Clap()
	{
		AniEnd_Clap_ = true;
	}

	void AniEnd_Reset()
	{
		AniEnd_Intro_ = false;
		AniEnd_Attack_Body_Birth_ = false;
		AniEnd_Attack_Body_End_ = false;
		AniEnd_Attack_Hand_Birth_ = false;
	}

#endif // _DEBUG

#ifndef _DEBUG
	void AniEnd_Intro()
	{
		State_.ChangeState("Idle");
	}
	void AniEnd_Attack_Body_Birth()
	{
		MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Idle");

		Hand_.HandOn();
		Hand_.ImageRenderer->SetChangeAnimation("KDice-Attack-Hand-Birth");

		Hand_.IsAttacking_ = true;
	}
	void AniEnd_Attack_Body_End()
	{
		State_.ChangeState("Idle");
	}
	void AniEnd_Attack_Hand_Birth()
	{
		Hand_.ImageRenderer->SetChangeAnimation("KDice-Attack-Hand-Idle");
	}
	void AniEnd_Clap()
	{
		MonsterImageRenderer->SetChangeAnimation("KDice-Idle");
		AniEnd_Clap_ = true;
	}
#endif // _DEBUG



};

