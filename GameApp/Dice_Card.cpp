#include "PreCompile.h"
#include "Dice_Card.h"

Dice_Card::Dice_Card()
	: Collision(nullptr)
	, ImageRenderer(nullptr)
{
}

Dice_Card::~Dice_Card()
{
}

void Dice_Card::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	Collision = CreateTransformComponent<GameEngineCollision>();

	ImageRenderer->GetTransform()->SetLocalPosition(float4{ 0.f, -50.f, static_cast<int>(ZOrder::Z01Actor04) });
	Collision->GetTransform()->SetLocalPosition(float4{ 0.f, -50.f, static_cast<int>(ZOrder::Z01Actor04) });

	Collision->SetCollisionType(CollisionType::Rect);
}

void Dice_Card::Update(float _DeltaTime)
{
	ImageRenderer->GetTransform()->SetWorldMove(CardMove_* _DeltaTime);
	Collision->GetTransform()->SetWorldMove(CardMove_ * _DeltaTime);

	GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
}


