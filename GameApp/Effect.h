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
	Effect(); // default constructer ����Ʈ ������
	~Effect(); // default destructer ����Ʈ �Ҹ���

	Effect(const Effect& _other) = delete; // default Copy constructer ����Ʈ ���������
	Effect(Effect&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	Effect& operator=(const Effect& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Effect& operator=(const Effect&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	EffectType EffectType_;

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);
};

