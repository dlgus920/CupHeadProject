#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class CbufferHeader
{
private:	// member Var

public:
	CbufferHeader(); // default constructer ����Ʈ ������
	~CbufferHeader(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	CbufferHeader(const CbufferHeader& _other) = delete; // default Copy constructer ����Ʈ ���������
	CbufferHeader(CbufferHeader&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	CbufferHeader& operator=(const CbufferHeader& _other) = delete; // default Copy operator ����Ʈ ���� ������
	CbufferHeader& operator=(const CbufferHeader&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

