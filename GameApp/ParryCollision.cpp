#include "PreCompile.h"
#include "ParryCollision.h"

ParryCollision::ParryCollision()
	: Parry_(false)
{
}

ParryCollision::~ParryCollision() // default destructer ����Ʈ �Ҹ���
{
}

void ParryCollision::Parry()
{
	Parry_ = true;
}

