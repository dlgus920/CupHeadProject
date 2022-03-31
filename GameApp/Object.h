#pragma once
#include "Image.h"
#include <GameEngine/GameEngineCollision.h>

// �з� : 
// �뵵 : 
// ���� : 
class Object : public Image
{
public:
	Object(); 
	~Object();

	Object(const Object& _other) = delete; 
	Object(Object&& _other) = delete;
	Object& operator=(const Object& _other) = delete; 
	Object& operator=(const Object&& _other) = delete; 

private:	// member Var
	void Start() final;
	void Update(float _DeltaTime) final;

private:
	GameEngineCollision* ObjectCollision_;
public:

	GameEngineCollision* GetObjectCollision()
	{
		return ObjectCollision_;
	}

};

