#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class Store
{
private:	// member Var

public:
	Store(); // default constructer ����Ʈ ������
	~Store(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Store(const Store& _other) = delete; // default Copy constructer ����Ʈ ���������
	Store(Store&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Store& operator=(const Store& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Store& operator=(const Store&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

