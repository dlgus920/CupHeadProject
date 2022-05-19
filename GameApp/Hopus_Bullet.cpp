#include "Precompile.h"
#include "Hopus_Bullet.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

Hopus_Bullet::Hopus_Bullet() 
	: Roll_(false)
	, TimeCheck_(0.f)
	, Dist_(0.f)
	, FireImageRenderer{nullptr}
	, FireCollision{nullptr}
{
}

Hopus_Bullet::~Hopus_Bullet()
{
}

void Hopus_Bullet::Start()
{
	for (int i = 0; i < 8; ++i)
	{
		FireImageRenderer[i] = CreateTransformComponent<GameEngineImageRenderer>();

		FireImageRenderer[i]->GetTransform()->SetLocalScaling(float4{});

		FireImageRenderer[i]->CreateLevelAnimation("Rabit_Skull.png", "Rabit_Skull", 0, 10, 0.04f, true);
		FireImageRenderer[i]->SetChangeAnimation("Rabit_Skull");

		FireCollision[i] = CreateTransformComponent<GameEngineCollision>();
		FireCollision[i]->SetCollisionType(CollisionType::Rect);
		FireCollision[i]->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
		FireCollision[i]->GetTransform()->SetLocalScaling(float4{});
	}

	Hopus_Bullet::Off();
}

void Hopus_Bullet::Update(float _DeltaTime)
{
	if (true == Roll_)
	{
		TimeCheck_ += _DeltaTime;

		GetTransform()->SetLocalRotationDegree(float4{} *_DeltaTime); // -> 회전 결과 3초뒤 다시 원위치로 돌아와야함

		if (TimeCheck_ >= 3.f)
		{
			Roll_ = false; 
		}
	}

	else
	{
		Dist_ -= _DeltaTime * 100.f;

		if (Dist_ <= 50.f)
		{
			Off();
		}

		for (int i = 0; i < 8; ++i)
		{
			FireImageRenderer[i]->GetTransform()->SetLocalPosition(float4{
				Dist_ * cosf(i * 45.f * GameEngineMath::DegreeToRadian),
				Dist_ * sinf(i * 45.f * GameEngineMath::DegreeToRadian) });

			FireCollision[i]->GetTransform()->SetLocalPosition(float4{
				Dist_ * cosf(i * 45.f * GameEngineMath::DegreeToRadian),
				Dist_ * sinf(i * 45.f * GameEngineMath::DegreeToRadian) });
		}
	}
}

void Hopus_Bullet::Reset()
{
	Hopus_Bullet::On();
	TimeCheck_ = 0.f;
	Roll_ = true;
	Dist_ = 300.f;

	for (int i = 0; i < 8; ++i)
	{
		FireImageRenderer[i]->GetTransform()->SetLocalPosition(float4{
			Dist_ * cosf(i * 45.f * GameEngineMath::DegreeToRadian),
			Dist_ * sinf(i * 45.f * GameEngineMath::DegreeToRadian) });

		FireCollision[i]->GetTransform()->SetLocalPosition(float4{
			Dist_ * cosf(i * 45.f * GameEngineMath::DegreeToRadian),
			Dist_ * sinf(i * 45.f * GameEngineMath::DegreeToRadian) });
	}

}
