#include "PreCompile.h"
#include "Effect.h"
#include "Monster.h"

Monster::Monster()
	: Hp_(0)
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
}

void Monster::TransformUpdate()
{
}

void Monster::Update(float _DeltaTime)
{
}

void Monster::ReleaseEvent()
{
}

void Monster::DamageToMonster(int _Damage)
{
	Hp_ -= _Damage;
}

void Monster::EffectDefeat(float4 _Pos)
{
	Effect* effect = GetLevel()->CreateActor<Effect>();
	effect->EffectAnimationActor("BossExplosion.png", "BossExplosion", 0, 9, 0.04, false);
	effect->GetTransform()->SetWorldPosition(_Pos);
}

void Monster::EffectDefeatRandom(float _Radius)
{
	float dist = Random_.RandomFloat(0.f, _Radius);
	float RanDegree = Random_.RandomFloat(0.f, 360.f);

	RanDegree *= GameEngineMath::DegreeToRadian;

	float4 Pos = float4{ cosf(RanDegree) * dist,sinf(RanDegree) * dist };

	Pos += GetTransform()->GetWorldPosition();

	EffectDefeat(Pos);
}