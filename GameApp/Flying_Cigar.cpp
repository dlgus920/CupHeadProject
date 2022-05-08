#include "PreCompile.h"

#include "Flying_Cigar.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Flying_Cigar::Flying_Cigar() 
	: Flying_CigarHitBox_(nullptr)
	, Flying_CigarImageRenderer_(nullptr)
{
}

Flying_Cigar::~Flying_Cigar() // default destructer 디폴트 소멸자
{
}

void Flying_Cigar::Start()
{
	Flying_CigarHitBox_ = CreateTransformComponent<GameEngineCollision>();
	Flying_CigarHitBox_->SetCollisionType(CollisionType::Rect);
	Flying_CigarHitBox_->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);

	Flying_CigarImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Flying_CigarImageRenderer_->CreateLevelAnimation("Fly_cigar.png","Fly_cigar",0,19,0.04f);
	Flying_CigarImageRenderer_->SetChangeAnimation("Fly_cigar");

	GetTransform()->SetLocalScaling(float4{200.f,230.f});
}

void Flying_Cigar::Update(float _DeltaTime)
{
}

