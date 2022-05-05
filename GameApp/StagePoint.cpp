#include "PreCompile.h"
#include "StagePoint.h"

StagePoint::StagePoint() // default constructer 디폴트 생성자
{

}

StagePoint::~StagePoint() // default destructer 디폴트 소멸자
{

}

void StagePoint::Start()
{
	ObjectCollision_ = CreateTransformComponent<GameEngineCollision>();
	ObjectRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();

	ObjectRenderer_->SetLevelImage("world_platforming_icon_0001.png");

	float4 size = ObjectRenderer_->GetImageSize();

	ObjectRenderer_->GetTransform()->SetLocalScaling(size);
	ObjectCollision_->GetTransform()->SetLocalScaling(size);

	ObjectCollision_->SetCollisionGroup(CollisionGruop::StagePoint);
	ObjectCollision_->SetCollisionType(CollisionType::Rect);
}

void StagePoint::Update(float _DeltaTime)
{
}

