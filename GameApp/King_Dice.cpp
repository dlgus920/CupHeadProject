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
		MonsterImageRenderer->CreateAnimationFolder("KDice-Idle","KDIce-idle",0.1);
	}

	float4 MonsterSize; //temp

	//{
	//	MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
	//	MonsterHitBox->CreateCollision<CollisionGruop>(CollisionType::Rect, CollisionGruop::Bullet, MonsterSize);
	//}

	MonsterImageRenderer->SetChangeAnimation("KDice-Idle");
}

void King_Dice::Update(float _DeltaTime)
{
}


