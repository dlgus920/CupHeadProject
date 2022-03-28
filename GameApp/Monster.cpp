#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include "Monster.h"

Monster::Monster() :
	State_(this),
	MonsterHitBox(nullptr),
	MonsterGroundCollision(nullptr),
	MonsterImageRenderer(nullptr),
	CurState_()

{
}

Monster::~Monster()
{
}

void Monster::ChangeAnimation(std::string _animation)
{
	MonsterImageRenderer->SetChangeAnimation(_animation);
}

void Monster::Start()
{
	{
		MonsterImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		MonsterImageRenderer->CreateAnimationFolder("KDIce-idle", "KDIce-idle", 0.04);
		MonsterImageRenderer->GetTransform()->SetLocalScaling({ 950.f, 480.0f, 1.0f });

		//MonsterImageRenderer->GetTransform()->SetLocalPosition();
	}

	//{
	//	MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
	//	MonsterHitBox->CreateCollision<CollisionGruop>(CollisionType::Rect, CollisionGruop::Bullet, MonsterSize);
	//}

	MonsterImageRenderer->SetChangeAnimation("KDIce-idle");

}

void Monster::TransformUpdate()
{
}

void Monster::Update(float _DeltaTime)
{

}

void Monster::ReleaseEvent()
{
}
