#pragma once
#include <GameEngine/GameEngineActor.h>

class ParryObject : public GameEngineActor
{
public:
	ParryObject(); 
	~ParryObject(); 

private:	
	ParryObject(const ParryObject& _other) = delete; 
	ParryObject(ParryObject&& _other) = delete;
	ParryObject& operator=(const ParryObject& _other) = delete; 
	ParryObject& operator=(const ParryObject&& _other) = delete; 

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);

public:

private:
	float TimeCheck_;

protected:
	class GameEngineCollision* ParryCollision;
	bool Parry_;

public:
	virtual void Parry(GameEngineCollision* ParriedCollision);

	void ParryObjectSetColOption(CollisionType _CollisionType, CollisionGruop _CollisionGruop);
};

