#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class Dice_Card
{
private:	// member Var

public:
	Dice_Card(); // default constructer ����Ʈ ������
	~Dice_Card(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Dice_Card(const Dice_Card& _other) = delete; // default Copy constructer ����Ʈ ���������
	Dice_Card(Dice_Card&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Dice_Card& operator=(const Dice_Card& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Dice_Card& operator=(const Dice_Card&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

