#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class Player_Update
{
private:	// member Var

public:
	Player_Update(); // default constructer ����Ʈ ������
	~Player_Update(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Player_Update(const Player_Update& _other) = delete; // default Copy constructer ����Ʈ ���������
	Player_Update(Player_Update&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Player_Update& operator=(const Player_Update& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Player_Update& operator=(const Player_Update&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

