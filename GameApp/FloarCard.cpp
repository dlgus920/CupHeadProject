#include "Precompile.h"
#include "FloarCard.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

FloarCard::FloarCard()
	: ImageRenderer(nullptr)
	, Collision(nullptr)
{
}

FloarCard::~FloarCard()
{
}

void FloarCard::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	ImageRenderer->CreateLevelAnimation("FloarCard.png", "FloarCard", 0, 2, 0.04f, true);
	ImageRenderer->SetChangeAnimation("FloarCard");
	ImageRenderer->GetTransform()->SetLocalScaling(float4{ 280.f, 80.f,1.f });

	Collisiondummy = CreateTransformComponent<GameEngineCollision>();
	Collisiondummy->GetTransform()->SetLocalScaling(float4{ 220.f, 10.f,1.f });


	Collision = CreateTransformComponent<GameEngineCollision>();
	Collision->SetCollisionType(CollisionType::Rect);
	Collision->SetCollisionGroup<CollisionGruop>(CollisionGruop::FloarCard);
	Collision->GetTransform()->SetLocalScaling(float4{ 120.f, 10.f,1.f });
}

void FloarCard::Update(float _DeltaTime)
{
	if (true == UserGame::StageInfo_.Debug_)
	{
		if (true == Collision->IsUpdate())
		{
			GetLevel()->PushDebugRender(Collisiondummy->GetTransform(), CollisionType::Rect, float4::GREEN);
		}
	}
}
