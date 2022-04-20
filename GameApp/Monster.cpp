#include "PreCompile.h"
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
