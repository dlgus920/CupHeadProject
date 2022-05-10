#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>

#include "Bullet.h"
#include "Image.h"
#include "Effect.h"
#include "Monster.h"

Bullet_Defalut::Bullet_Defalut()
{
}

Bullet_Defalut::~Bullet_Defalut()
{
}

void Bullet_Defalut::Start()
{
	Bullet::Start();

	BulletLifeTile_ = 2.f;

	BulletRenderer_->GetTransform()->SetLocalScaling(float4{ 150.f,64.f,1.f });
	BulletRenderer_->CreateLevelAnimation("Bullet_Default.png", "Idle", 0, 5, 0.04f);
	BulletRenderer_->SetChangeAnimation("Idle");

	BulletCollision_->GetTransform()->SetLocalScaling(float4{ 100.f,32.f,1.f });
	BulletCollision_->SetCollisionGroup<CollisionGruop>(CollisionGruop::Bullet);
	BulletCollision_->SetCollisionType(CollisionType::Rect);
}

void Bullet_Defalut::Update(float _DeltaTime)
{
	GameEngineCollision* MonsCol = BulletCollision_->CollisionPtr(static_cast<int>(CollisionGruop::MonsterHitBox));

	if (nullptr != MonsCol)
	{
		dynamic_cast<Monster*>(MonsCol->GetActor())->DamageToMonster(BulletInfo_.BulletDamage_);
		BulletDeath();
	}

	else
	{
		BulletLifeTile_ -= _DeltaTime;

		if (BulletLifeTile_ == 0.f)
		{
			BulletDeath();
		}

		GetTransform()->SetWorldMove(BulletInfo_.MoveDir_ * BulletInfo_.BulletSpeed_ * _DeltaTime);
	}
}

void Bullet_Defalut::BulletDeath()
{
	Effect* Birth = GetLevel()->CreateActor<Effect>();
	Birth->EffectAnimationActor("Bullet_Default_Death.png", "Death", float4{ 280.f,280.f }, 0, 5, 0.04f, false);
	Birth->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());

	Death();
}
