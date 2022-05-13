#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) = delete;

protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);
	virtual void ReleaseEvent();

protected:
	GameEngineRandom Random_;
	int Hp_;

public:
	void DamageToMonster(int _Damage);

protected:

	void EffectDefeat(float4 _Pos);
	void EffectDefeatRandom(float _Radius, float4 _Pos);


};
