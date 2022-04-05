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

	BulletRenderer_->CreateAnimation("Bullet_Default.png", "Idle", 0, 5, 0.1f);
	BulletRenderer_->SetEndCallBack("Idle", std::bind(&Bullet_Defalut::Death, this));

	BulletRenderer_->SetChangeAnimation("Idle");

	BulletRenderer_->SetAdjustImzgeSize();
}

void Bullet_Defalut::Update(float _DeltaTime)
{
	//if (true == BulletCollisionCheck(CollisionGruop::Player))
	//{
	//	BulletCollisionSpawnEffect<Bullet>(CollisionGruop::Player);
	//}

	GetTransform()->SetWorldMove
	(BulletInfo_.MoveDir_ * BulletInfo_ .BulletSpeed_* _DeltaTime);
}