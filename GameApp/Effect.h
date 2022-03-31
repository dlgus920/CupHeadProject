#pragma once
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineActor.h>

enum class EffectType
{
	None,
	Dust,
	Shoot_Birth,
	Shoot_Death,
	SShoot_Birth,
	SShoot_Death,
	//inline 함수로 인스턴스하게 ㅏ용
};

class Effect : public GameEngineActor
{
public:
	Effect(); // default constructer 디폴트 생성자
	~Effect(); // default destructer 디폴트 소멸자

	Effect(const Effect& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Effect(Effect&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	Effect& operator=(const Effect& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Effect& operator=(const Effect&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	EffectType EffectType_;

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);
};

