#pragma once
#include "ParryObject.h"

// 만들어진 상태에서 아예 안쓸때까지 소멸되지 않고 메모리에 남아있게 함 // 일일이 다시 만드는데 되려 메모리 먹음
enum class DiceNumber
{
	None,
	Num1,
	Num2,
	Num3
};
class PerryObjectDice : public ParryObject
{
public:
	PerryObjectDice();
	~PerryObjectDice();

	PerryObjectDice(const PerryObjectDice& _other) = delete;
	PerryObjectDice(PerryObjectDice&& _other) = delete;
	PerryObjectDice& operator=(const PerryObjectDice& _other) = delete;
	PerryObjectDice& operator=(const PerryObjectDice&& _other) = delete;

private:	// member Var
	class GameEngineImageRenderer* ObjectRenderer_;

	DiceNumber DiceNumber_;
	bool Rolled_;
	class King_Dice* King_Dice_;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetKing_Dice(King_Dice* _King_Dice)
	{
		King_Dice_ = _King_Dice;
	}

private:
	void Resset();

	void Num1();
	void Num2();
	void Num3();

	void Rolling1_1();
	void Rolling2_1();
	void Rolling3_1();

	void Rolling1_2();
	void Rolling2_2();
	void Rolling3_2();

	void RollingEnd();

public:
	const int GetNumber()
	{
		return static_cast<int>(DiceNumber_);
	}

	const bool GetRoll()
	{
		return Rolled_;
	}

};

