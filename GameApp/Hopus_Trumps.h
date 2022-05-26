#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ParryObject.h"
#include <GameEngineBase/GameEngineRandom.h>

class GameEngineCollision;
class GameEngineImageRenderer;
class Hopus_Trumps : public ParryObject
{
public:
	Hopus_Trumps();
	~Hopus_Trumps();

	Hopus_Trumps(const Hopus_Trumps& _other) = delete;
	Hopus_Trumps(Hopus_Trumps&& _other) = delete;
	Hopus_Trumps& operator=(const Hopus_Trumps& _other) = delete;
	Hopus_Trumps& operator=(const Hopus_Trumps&& _other) = delete;

private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	struct TrumpBullet
	{
		TrumpBullet() {};
		~TrumpBullet() {};

		GameEngineImageRenderer* TrumpImageRenderer_;
		GameEngineCollision* TrumpCollision_;
	};


	GameEngineRandom Rand_;

	GameEngineImageRenderer* FireImageRenderer_[9];
	GameEngineCollision* FireCollision_[9];

	//class ParryObject* ParryObject_[2];

	float4 Blendlate_;

	int Trumpsorder_[9];

	int ParryNum_[2];

	bool BlendStart_;
	bool Pos_Up_;

	bool AttackStart_;

	float TimeCheck_;

public:
	void Parry(GameEngineCollision* ParriedCollision) override;

	void Reset();

	void AttackStart()
	{
		AttackStart_ = true;
	}

};

