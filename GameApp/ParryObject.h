#pragma once
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class ParryObject : public GameEngineActor
{
protected:
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

protected:
	bool Parry_;

public:
	void Parry();
};

