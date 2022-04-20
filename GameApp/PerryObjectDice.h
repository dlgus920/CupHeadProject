#pragma once
#include "ParryObject.h"

// ������� ���¿��� �ƿ� �Ⱦ������� �Ҹ���� �ʰ� �޸𸮿� �����ְ� �� // ������ �ٽ� ����µ� �Ƿ� �޸� ����
enum class DiceNumber
{
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
	GameEngineCollision* ObjectCollision_;
	GameEngineImageRenderer* ObjectRenderer_;

	DiceNumber DiceNumber_;
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

