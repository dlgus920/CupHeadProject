#include "PreCompile.h"
#include "ParryObject.h"

ParryObject::ParryObject() 
	: Parry_(false)
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

void ParryObject::Parry()
{
	Parry_ = true;
}
