#pragma once
#include "Image.h"
#include <GameEngine/GameEngineCollision.h>

// 분류 : 
// 용도 : 
// 설명 : 
class Object : public GameEngineActor
{
public:
	Object(); 
	~Object();

	Object(const Object& _other) = delete; 
	Object(Object&& _other) = delete;
	Object& operator=(const Object& _other) = delete; 
	Object& operator=(const Object&& _other) = delete; 

protected:	// member Var
	virtual void Start();
	virtual void Update(float _DeltaTime);

protected:
	GameEngineCollision* ObjectCollision_;
	GameEngineImageRenderer* ObjectRenderer_;

public:

	GameEngineCollision* GetObjectCollision()
	{
		return ObjectCollision_;
	}

	GameEngineImageRenderer* GetObjectRenderer()
	{
		return ObjectRenderer_;
	}

};

