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
	BulletHitBox_->SetCollisionType(CollisionType::Rect);
	BulletHitBox_->SetCollisionGroup(static_cast<int>(CollisionGruop::Bullet));

}

void Bullet_Guided::Update(float _DeltaTime)
{
}
