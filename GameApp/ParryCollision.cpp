#include "PreCompile.h"
#include "ParryCollision.h"

ParryCollision::ParryCollision()
	: Parry_(false)
{
}

ParryCollision::~ParryCollision() // default destructer 디폴트 소멸자
{
}

void ParryCollision::Parry()
{
	Parry_ = true;
}

