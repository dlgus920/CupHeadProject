#pragma once
#include "ParryObject.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

class Dice_Card : public ParryObject
{
	friend class King_Dice;
public:
	Dice_Card();
	~Dice_Card();

	Dice_Card(const Dice_Card& _other) = delete;
	Dice_Card(Dice_Card&& _other) = delete;
	Dice_Card& operator=(const Dice_Card& _other) = delete;
	Dice_Card& operator=(const Dice_Card&& _other) = delete;

private:
	GameEngineImageRenderer* ImageRenderer;
	GameEngineCollision* Collision;
	float4 CardMove_;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetCardMove(float4 _CardMove)
	{
		CardMove_ = _CardMove;
	}
};
