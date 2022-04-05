#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "Bullet.h"

Bullet::Bullet() :
	BulletCollision_(nullptr),
	BulletRenderer_(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	BulletRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	BulletCollision_ = CreateTransformComponent<GameEngineCollision>();
}

void Bullet::Update(float _DeltaTime)
{
}

void Bullet::SetBulletInfo(BulletInfo _BulletInfo)
{
	BulletInfo_ = _BulletInfo;

	float degree = float4::DegreeDot3DToACosAngle(float4::RIGHT, _BulletInfo.MoveDir_);
	
	//float degree = atanf(_BulletInfo.MoveDir_.y / _BulletInfo.MoveDir_.x);
	//degree *= GameEngineMath::RadianToDegree;

	BulletRenderer_->GetTransform()->SetLocalRotation(float4{ 0.f,0.f,degree });
	BulletCollision_->GetTransform()->SetLocalRotation(float4{ 0.f,0.f,degree });
}




