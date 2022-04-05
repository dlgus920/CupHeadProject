#pragma once
#include "Object.h"

class StagePoint : public Object
{
public:
	StagePoint(); // default constructer 디폴트 생성자
	~StagePoint(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	StagePoint(const StagePoint& _other) = delete; // default Copy constructer 디폴트 복사생성자
	StagePoint(StagePoint&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	StagePoint& operator=(const StagePoint& _other) = delete; // default Copy operator 디폴트 대입 연산자
	StagePoint& operator=(const StagePoint&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
private:	// member Var

public:
	void Start() override;
	void Update(float _DeltaTime) override;
};

