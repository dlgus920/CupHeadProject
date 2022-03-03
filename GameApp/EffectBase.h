#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class EffectBase : public GameEngineActor
{
private:	// member Var

public:
	EffectBase(); // default constructer 디폴트 생성자
	~EffectBase(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	EffectBase(const EffectBase& _other) = delete; // default Copy constructer 디폴트 복사생성자
	EffectBase(EffectBase&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	EffectBase& operator=(const EffectBase& _other) = delete; // default Copy operator 디폴트 대입 연산자
	EffectBase& operator=(const EffectBase&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);
	virtual void ReleaseEvent();
};

