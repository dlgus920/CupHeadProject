#include "PreCompile.h"
#include "King_Dice.h"

King_Dice::King_Dice()
	: State_(this)
	
{
}

King_Dice::~King_Dice() // default destructer 디폴트 소멸자
{
}

void King_Dice::Start()
{
	{
		MonsterImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		MonsterImageRenderer->CreateAnimationFolder("KDIce-idle", "KDIce-idle", 0.04);
		MonsterImageRenderer->GetTransform()->SetLocalScaling({ 950.f, 480.0f, 1.0f });

		//MonsterImageRenderer->GetTransform()->SetLocalPosition();
	}

	{
		MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBox->SetCollisionType(CollisionType::Rect);
		MonsterHitBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		MonsterHitBox->GetTransform()->SetLocalScaling(float4{200.f,200.f,1.f});
	}

	MonsterImageRenderer->SetChangeAnimation("KDIce-idle");
}

void King_Dice::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);

}


