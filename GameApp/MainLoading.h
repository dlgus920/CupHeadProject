#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class MainLoading
{
private:	// member Var

public:
	MainLoading(); // default constructer ����Ʈ ������
	~MainLoading(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MainLoading(const MainLoading& _other) = delete; // default Copy constructer ����Ʈ ���������
	MainLoading(MainLoading&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MainLoading& operator=(const MainLoading& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MainLoading& operator=(const MainLoading&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

