#include "PreCompile.h"
#include "ParryObject.h"

ParryObject::ParryObject() 
	: Parry_(false)
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
}

void ParryObject::Parry()
{
	Parry_ = true;
}
