#include "PreCompile.h"
#include "StagePoint.h"

StagePoint::StagePoint() // default constructer ����Ʈ ������
{

}

StagePoint::~StagePoint() // default destructer ����Ʈ �Ҹ���
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

