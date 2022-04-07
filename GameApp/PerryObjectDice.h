#pragma once
#include "Object.h"

// 만들어진 상태에서 아예 안쓸때까지 소멸되지 않고 메모리에 남아있게 함 // 일일이 다시 만드는데 되려 메모리 먹음
enum class DiceNumber
{
	Num1,
	Num2,
	Num3
};
class PerryObjectDice : public Object
{
public:
	PerryObjectDice();
	~PerryObjectDice();

	PerryObjectDice(const PerryObjectDice& _other) = delete;
	PerryObjectDice(PerryObjectDice&& _other) = delete;
	PerryObjectDice& operator=(const PerryObjectDice& _other) = delete;
	PerryObjectDice& operator=(const PerryObjectDice&& _other) = delete;

private:	// member Var
	DiceNumber DiceNumber_;
	bool IsCollision_;
public:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Resset();

	void Num1()
	{
		DiceNumber_ = DiceNumber::Num1;
	}
	void Num2()
	{
		DiceNumber_ = DiceNumber::Num2;
	}
	void Num3()
	{
		DiceNumber_ = DiceNumber::Num3;
	}

	void Rolling1_1();
	void Rolling2_1();
	void Rolling3_1();

	void Rolling1_2();
	void Rolling2_2();
	void Rolling3_2();

	void RollingEnd();

};

