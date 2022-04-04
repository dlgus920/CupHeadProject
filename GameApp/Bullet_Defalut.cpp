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
	GetTransform()->SetWorldPosition(float4::ZERO);

	{
		ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		ImageRenderer_->GetTransform()->SetWorldPosition(float4::ZERO);
		ImageRenderer_->CreateAnimation("Bullet_Default.png", "Idle", 0, 5, 0.1f);
		ImageRenderer_->SetEndCallBack("Idle",std::bind(&Bullet_Defalut::Death,this));
	}

	ImageRenderer_->SetChangeAnimation("Idle");
	ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 100.f,50.f,1.f });
}

void Bullet_Defalut::Update(float _DeltaTime)
{
	GetTransform()->SetLocalMove(MoveDir_ * 600.f* _DeltaTime);
}