#pragma once
#include "Object.h"

class StagePoint : public Object
{
public:
	StagePoint(); // default constructer ����Ʈ ������
	~StagePoint(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	StagePoint(const StagePoint& _other) = delete; // default Copy constructer ����Ʈ ���������
	StagePoint(StagePoint&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	StagePoint& operator=(const StagePoint& _other) = delete; // default Copy operator ����Ʈ ���� ������
	StagePoint& operator=(const StagePoint&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
private:	// member Var

public:
	void Start() override;
	void Update(float _DeltaTime) override;
};

