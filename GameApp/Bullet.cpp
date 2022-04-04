#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "Bullet.h"

Bullet::Bullet() :
	MoveDir_(),
	BulletHitBox_(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{	
}

void Bullet::TransformUpdate()
{
}

void Bullet::Update(float _DeltaTime)
{
}

void Bullet::ReleaseEvent()
{
	
}

void Bullet::BulletRotate(float4 _Rot)
{
	GetTransform()->SetLocalRotation(_Rot);
}

void Bullet::BulletMove(float4 _Pos)
{
	GetTransform()->SetLocalPosition(_Pos);
}

void Bullet::BulletScale(float _x, float _y)
{
	//BulletHitBox_->GetTransform()->SetLocalScaling(_x,_y);
	//ImageRenderer_->GetTransform()->SetLocalScaling(_x, _y);
}

void Bullet::BulletSort(float _Zorder)
{
}




