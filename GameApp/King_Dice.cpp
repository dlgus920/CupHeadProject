#include "PreCompile.h"
#include "King_Dice.h"

King_Dice::King_Dice() // default constructer ����Ʈ ������
{
}

King_Dice::~King_Dice() // default destructer ����Ʈ �Ҹ���
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


