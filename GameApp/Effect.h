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
	//inline �Լ��� �ν��Ͻ��ϰ� ����
};

class Effect : public GameEngineActor
{
public:
	Effect(); 
	~Effect();

private:
	Effect(const Effect& _other) = delete; 
	Effect(Effect&& _other) = delete; 
	Effect& operator=(const Effect& _other) = delete; 
	Effect& operator=(const Effect&& _other) = delete;

private:
	GameEngineImageRenderer* ImageRenderer_;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetDust();

};

