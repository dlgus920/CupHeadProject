#pragma once
#include "ParryObject.h"

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
	class GameEngineImageRenderer* ImageRenderer;
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
