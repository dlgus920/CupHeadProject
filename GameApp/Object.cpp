#include "PreCompile.h"
#include "Object.h"

Object::Object() // default constructer ����Ʈ ������
{

}

Object::~Object() // default destructer ����Ʈ �Ҹ���
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

