#include "PreCompile.h"
#include "Object.h"

Object::Object() // default constructer 디폴트 생성자
{

}

Object::~Object() // default destructer 디폴트 소멸자
{

}

void Object::Start()
{
	Image::Start();

	ObjectCollision_ = CreateTransformComponent<GameEngineCollision>();
}

void Object::Update(float _DeltaTime)
{
}

