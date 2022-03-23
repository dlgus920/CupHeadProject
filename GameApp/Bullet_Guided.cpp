#include "PreCompile.h"
#include "Bullet.h"

Bullet_Guided::Bullet_Guided() :
	Target_(nullptr),
	OriginDir_(),
	TargetDir_(),
	OriginSpeed_(0.f),
	TargetSpeed_(0.f)
{
}

Bullet_Guided::~Bullet_Guided()
{
}

void Bullet_Guided::Start()
{
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	//ImageRenderer_->CreateAnimation();



	BulletHitBox_ = CreateTransformComponent<GameEngineCollision>();
	BulletHitBox_->CreateCollision<CollisionGruop>
		(CollisionType::Rect, CollisionGruop::PlayerHitBox, float4{ 100.0f, 100.0f, 1.0f });

}

void Bullet_Guided::Update(float _DeltaTime)
{
}
