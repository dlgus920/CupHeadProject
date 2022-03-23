#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Bullet.h"

Bullet_Defalut::Bullet_Defalut()
{
}

Bullet_Defalut::~Bullet_Defalut()
{
}

void Bullet_Defalut::Start()
{
	{
		BulletHitBox_ = CreateTransformComponent<GameEngineCollision>();
		BulletHitBox_->CreateCollision<CollisionGruop>
			(CollisionType::Rect, CollisionGruop::PlayerHitBox, float4{ 100.0f, 100.0f, 1.0f });
	}

	{
		ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		ImageRenderer_->CreateAnimation("Bullet_Default.png", "Idle", 0, 5, 0.1f);
	}
}

void Bullet_Defalut::Update(float _DeltaTime)
{
	if (true == BulletCollisionCheck(CollisionGruop::Player))
	{
		BulletCollisionSpawnEffect<Bullet>(CollisionGruop::Player);
	}
}