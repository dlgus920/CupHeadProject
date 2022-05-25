#pragma once
#include <GameEngine/GameEngineCollision.h>
#include "AppGlobalValue.h"

// 분류 : 
// 용도 : 
// 설명 : 
class ParryCollision : public GameEngineCollision
{
public:
	ParryCollision();
	~ParryCollision();

private:	
	ParryCollision(const ParryCollision& _other) = delete;
	ParryCollision(ParryCollision&& _other) = delete;
	ParryCollision& operator=(const ParryCollision& _other) = delete;
	ParryCollision& operator=(const ParryCollision&& _other) = delete;

public:
	bool Parry_;

public:
	void Parry();

	void ParryObjectSetColOption(CollisionType _CollisionType, CollisionGruop _CollisionGruop)
	{
		SetCollisionType(_CollisionType);
		SetCollisionGroup<CollisionGruop>(_CollisionGruop);
	}

	bool GetParry()
	{
		return Parry_;
	}
};

