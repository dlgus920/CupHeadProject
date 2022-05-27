#include "PreCompile.h"
#include "Dice_Card.h"
#include "UserGame.h"

#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>

Dice_Card::Dice_Card()
	: ImageRenderer(nullptr)
{
}

Dice_Card::~Dice_Card()
{
}

void Dice_Card::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	ParryCollision = CreateTransformComponent<GameEngineCollision>();
	ParryCollision->SetCollisionType(CollisionType::Rect);

	ImageRenderer->GetTransform()->SetLocalPosition(float4{ 0.f, -50.f, static_cast<int>(ZOrder::Z01Actor04) });
	ParryCollision->GetTransform()->SetLocalPosition(float4{ 0.f, -50.f, static_cast<int>(ZOrder::Z01Actor04) });
}

void Dice_Card::Update(float _DeltaTime)
{
	ImageRenderer->GetTransform()->SetWorldMove(CardMove_* _DeltaTime);
	ParryCollision->GetTransform()->SetWorldMove(CardMove_ * _DeltaTime);

	if (true == UserGame::StageInfo_.Debug_)
	{
		GetLevel()->PushDebugRender(ParryCollision->GetTransform(), CollisionType::Rect);
	}
}


