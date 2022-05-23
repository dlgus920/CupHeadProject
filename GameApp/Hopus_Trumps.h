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
	GameEngineCollision* ParryCollision_[2];

	int Trumpsorder_[9];

	int ParryNum_;

	bool Roll_;
	float TimeCheck_;

public:
	void Reset(float4 _PlayerPos);

};

