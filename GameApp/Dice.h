#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class Dice
{
private:	// member Var

public:
	Dice(); // default constructer ����Ʈ ������
	~Dice(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Dice(const Dice& _other) = delete; // default Copy constructer ����Ʈ ���������
	Dice(Dice&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Dice& operator=(const Dice& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Dice& operator=(const Dice&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

