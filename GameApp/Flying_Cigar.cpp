#include "PreCompile.h"

#include "Flying_Cigar.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Flying_Cigar::Flying_Cigar() 
	: Flying_CigarHitBox_(nullptr)
	, Flying_CigarImageRenderer_(nullptr)
	, TimeCheck_(0.f)
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
	Flying_CigarHitBox_->GetTransform()->SetLocalScaling(float4{ 100.f,200.f });

	Flying_CigarImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Flying_CigarImageRenderer_->CreateLevelAnimation("Fly_cigar.png","Fly_cigar",0,19,0.04f);
	Flying_CigarImageRenderer_->SetChangeAnimation("Fly_cigar");
	Flying_CigarImageRenderer_->GetTransform()->SetLocalScaling(float4{ 200.f,230.f });

	FireRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	FireRenderer_->CreateLevelAnimation("Cigar_dust.png", "Cigar_dust", 0, 8, 0.04f, false);
	//FireRenderer_->SetEndCallBack("Cigar_dust", std::bind(&GameEngineImageRenderer::Off, FireRenderer_));
	FireRenderer_->SetChangeAnimation("Cigar_dust");
	FireRenderer_->GetTransform()->SetLocalScaling(float4{ 50.f,75.f });
	FireRenderer_->GetTransform()->SetLocalPosition(float4{ 0.f,-100.f });
}

void Flying_Cigar::Update(float _DeltaTime)
{
	if (true == UserGame::StageInfo_.Debug_)
	{
		GetLevel()->PushDebugRender(Flying_CigarHitBox_->GetTransform(), CollisionType::Rect);
	}

	TimeCheck_ += _DeltaTime;

	FireRenderer_->GetTransform()->SetWorldMove(float4{ 0.f,-200.f * _DeltaTime });

	if (TimeCheck_ >= 0.5f)
	{
		float4 pos = GetTransform()->GetWorldPosition();
		pos.y -= 100.f;

		FireRenderer_->SetCurAnimationFrame(0);
		FireRenderer_->GetTransform()->SetWorldPosition(pos);
		TimeCheck_ = 0.f;
	}
}

