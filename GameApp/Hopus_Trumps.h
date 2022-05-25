#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

class GameEngineCollision;
class GameEngineImageRenderer;
class Hopus_Trumps : public GameEngineActor
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
	GameEngineRandom Rand_;

	GameEngineImageRenderer* FireImageRenderer_[9];
	GameEngineCollision* FireCollision_[9];

	class ParryObject* ParryObject_[2];

	float4 Blendlate_;

	int Trumpsorder_[9];

	int ParryNum_[2];

	bool BlendStart_;
	bool Pos_Up_;

	bool AttackStart_;

	float TimeCheck_;

public:
	void Reset();

	void AttackStart()
	{
		AttackStart_ = true;
	}

};

