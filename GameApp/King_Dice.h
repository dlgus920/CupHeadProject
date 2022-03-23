#pragma once
#include "Monster.h"

// �з� : 
// �뵵 : 
// ���� : 
class King_Dice : public Monster
{
public:
	King_Dice(); // default constructer ����Ʈ ������
	~King_Dice(); // default destructer ����Ʈ �Ҹ���

	King_Dice(const King_Dice& _other) = delete; // default Copy constructer ����Ʈ ���������
	King_Dice(King_Dice&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	King_Dice& operator=(const King_Dice& _other) = delete; // default Copy operator ����Ʈ ���� ������
	King_Dice& operator=(const King_Dice&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;
public:
};

