#include "PreCompile.h"
#include "ParryObject.h"

#include <GameEngine/GameEngineCollision.h>

ParryObject::ParryObject() 
	: Parry_(false)
	, ParryCollision(nullptr)
{
}

ParryObject::~ParryObject() // default destructer ����Ʈ �Ҹ���
{
}

void ParryObject::Start()
{
}

void ParryObject::Update(float _DeltaTime)
{
}

void ParryObject::ParryObjectSetColOption(CollisionType _CollisionType, CollisionGruop _CollisionGruop)
{
	ParryCollision->SetCollisionType(_CollisionType);
	ParryCollision->SetCollisionGroup<CollisionGruop>(_CollisionGruop);
}
