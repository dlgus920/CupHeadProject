#include "Precompile.h"
#include "Wheezy_Fire.h"
#include "Effect.h"
#include "UserGame.h"

Wheezy_Fire::Wheezy_Fire()
	: FireHitBox_(nullptr)
	, FireImageRenderer_(nullptr)
	, fRotValue_(0.f)
	, fDirValue_(0.f)
	, TimeCheck_(0.f)
	, DeathTimeCheck_(0.f)
{
}

Wheezy_Fire::~Wheezy_Fire()
{
}

void Wheezy_Fire::Start()
{
	Component_ = CreateTransformComponent<RotCore>();
	ComponentChild_ = CreateTransformComponent<RotCore>(Component_->GetTransform());
	ComponentChild_->GetTransform()->SetLocalPosition(float4{ 0.f,-200.f });

	FireImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	FireImageRenderer_->GetTransform()->SetLocalScaling(float4{ 130.f,130.f, 1.f});
	FireImageRenderer_->CreateLevelAnimation("Wheezy_Fire.png", "Wheezy_Fire", 0, 2, 0.04f);
	FireImageRenderer_->SetChangeAnimation("Wheezy_Fire");

	FireHitBox_ = CreateTransformComponent<GameEngineCollision>();
	FireHitBox_->GetTransform()->SetLocalScaling(float4{ 100.f,100.f,1.f });
	FireHitBox_->SetCollisionType(CollisionType::Rect);
	FireHitBox_->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);

	float4 temppos = ComponentChild_->GetTransform()->GetWorldPosition();

	FireHitBox_->GetTransform()->SetWorldPosition(temppos);
	FireImageRenderer_->GetTransform()->SetWorldPosition(temppos);
}

void Wheezy_Fire::Update(float _DeltaTime)
{
	if (true == UserGame::StageInfo_.Debug_)
	{
		if (true == FireHitBox_->IsUpdate())
		{
			GetLevel()->PushDebugRender(FireHitBox_->GetTransform(), CollisionType::CirCle);
		}
	}

	TimeCheck_ += _DeltaTime;
	DeathTimeCheck_ += _DeltaTime;

	Component_->GetTransform()->SetMoveLocalRotationDegree(float4{ 0.f,0.f,fDirValue_*0.02f * _DeltaTime });
	Component_->GetTransform()->SetWorldMove(float4{ fDirValue_ * _DeltaTime,0.f });

	float4 temppos = ComponentChild_->GetTransform()->GetWorldPosition();

	FireHitBox_->GetTransform()->SetWorldPosition(temppos);
	FireImageRenderer_->GetTransform()->SetWorldPosition(temppos);
	FireImageRenderer_->GetTransform()->SetMoveLocalRotationDegree(float4{ 0.f,0.f,-fDirValue_ *0.1f });

	if (DeathTimeCheck_ > 5.f)
	{
		Death();
	}

	if (TimeCheck_ >= 0.1f)
	{
		temppos.z = static_cast<float>(ZOrder::Z01Actor02);
		GameEngineImageRenderer* FireRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		FireRenderer_->CreateLevelAnimation("Wheezy_Fire_Cloud.png", "Wheezy_Fire_Cloud", 0, 15, 0.04f, false);
		FireRenderer_->SetEndCallBack("Wheezy_Fire_Cloud", std::bind(&GameEngineImageRenderer::Death, FireRenderer_));
		FireRenderer_->SetChangeAnimation("Wheezy_Fire_Cloud");
		FireRenderer_->GetTransform()->SetLocalScaling(float4{ 100.f,100.f });
		FireRenderer_->GetTransform()->SetWorldPosition(temppos);

		TimeCheck_ = 0.f;
	}
}
