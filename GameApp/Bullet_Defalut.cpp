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
		BulletHitBox_->SetCollisionType(CollisionType::Rect);
		BulletHitBox_->SetCollisionGroup(static_cast<int>(CollisionGruop::PlayerHitBox));
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

	GetTransform()->SetWorldMove(MoveDir_);
}