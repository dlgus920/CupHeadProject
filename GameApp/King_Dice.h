#pragma once
#include "Monster.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineFSM.h>

class Dice_Card;

class King_Dice : public Monster
{
public:
	King_Dice(); // default constructer ����Ʈ ������
	~King_Dice(); // default destructer ����Ʈ �Ҹ���

	King_Dice(const King_Dice& _other) = delete; // default Copy constructer ����Ʈ ���������
	King_Dice(King_Dice&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	King_Dice& operator=(const King_Dice& _other) = delete; // default Copy operator ����Ʈ ���� ������
	King_Dice& operator=(const King_Dice&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	GameEngineFSM State_;
	GameEngineFSM BattleState_;

	GameEngineCollision* MonsterHitBox;

	GameEngineImageRenderer* MonsterImageRenderer;

	class PerryObjectDice* PerryObjectDice_;

	bool Defeat_;

	int CardCount_;
	float TimeCheck_;

	bool FirstAttack_;

	bool IsDiceTime_;

	bool Ani_Idle_Ready_;

	bool Attack_bgm_on_;

	bool AniEnd_Intro_;
	bool AniEnd_Attack_Body_Birth_;
	bool AniEnd_Attack_Body_End_;

	bool AniEnd_Attack_Hand_Birth_;

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

private:

	void AniEnd_Clap_Dice()
	{
		AniEnd_Clap_Dice_ = true;
	}

	void Ani_Idle_Ready()
	{
		Ani_Idle_Ready_ = true;
	}

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
};

