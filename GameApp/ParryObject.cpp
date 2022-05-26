#include "PreCompile.h"
#include "ParryObject.h"

#include <GameEngine/GameEngineCollision.h>

ParryObject::ParryObject() 
	: Parry_(false)
	, ParryCollision(nullptr)
	, TimeCheck_(0.f)
{
}

ParryObject::~ParryObject() // default destructer 디폴트 소멸자
{
}

void ParryObject::Start()
{
}

void ParryObject::Update(float _DeltaTime)
{
	if (Parry_ = true)
	{
		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 0.5f)
		{
			Parry_ = false;
			TimeCheck_ = 0.f;
		}
	}
}

void ParryObject::Parry(GameEngineCollision* ParriedCollision)
{
	Parry_ = true;

	ParryCollision = ParriedCollision;
}

void ParryObject::ParryObjectSetColOption(CollisionType _CollisionType, CollisionGruop _CollisionGruop)
{
	ParryCollision->SetCollisionType(_CollisionType);
	ParryCollision->SetCollisionGroup<CollisionGruop>(_CollisionGruop);
}
