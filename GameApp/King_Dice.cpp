#include "PreCompile.h"
#include "King_Dice.h"

King_Dice::King_Dice() // default constructer 디폴트 생성자
{
}

King_Dice::~King_Dice() // default destructer 디폴트 소멸자
{
}

void King_Dice::Start()
{
	{
		MonsterImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		//MonsterImageRenderer->CreateAnimation();
	}

	float4 MonsterSize; //temp

	{
		MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBox->CreateCollision<CollisionGruop>(CollisionType::Rect, CollisionGruop::Bullet, MonsterSize);
	}
}

void King_Dice::Update(float _DeltaTime)
{
}


