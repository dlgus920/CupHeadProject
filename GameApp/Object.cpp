#include "PreCompile.h"
#include "Object.h"

Object::Object()
	: ObjectCollision_(nullptr)
	, ObjectRenderer_(nullptr)

{

}

Object::~Object() // default destructer 디폴트 소멸자
{

}

void Object::Start()
{
	ObjectRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	ObjectCollision_ = CreateTransformComponent<GameEngineCollision>();
}

void Object::Update(float _DeltaTime)
{
}

