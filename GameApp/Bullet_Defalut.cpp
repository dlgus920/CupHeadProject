#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Bullet.h"
#include "Image.h"

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

	BulletRenderer_->CreateAnimation("Bullet_Default.png", "Idle", 0, 5, 0.05f);
	//BulletRenderer_->SetEndCallBack("Idle", std::bind(&Bullet_Defalut::Death, this));

	BulletRenderer_->SetChangeAnimation("Idle");

	BulletRenderer_->SetAdjustImzgeSize();


	BulletCollision_->SetCollisionGroup<CollisionGruop>(CollisionGruop::Bullet);
	BulletCollision_->SetCollisionType(CollisionType::Rect);
	BulletCollision_->GetTransform()->SetLocalScaling(float4{ 100.f,32.f,1.f });
}

void Bullet_Defalut::Update(float _DeltaTime)
{
	if (true == BulletCollisionCheck(CollisionGruop::MonsterHitBox))
	{
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
	Image* Birth = GetLevel()->CreateActor<Image>();
	Birth->ImageCreateAnimation("Bullet_Default_Death.png", "Death", 0, 5, 0.05, false);
	Birth->SetReserveDeath("Death");
	Birth->SetAdjustImzgeSize();
	Birth->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());

	Death();
}
