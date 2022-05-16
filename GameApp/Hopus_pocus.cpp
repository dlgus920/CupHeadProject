#include "PreCompile.h"
#include "Hopus_pocus.h"
#include "Effect.h"
#include "Wheezy_Fire.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Hopus_pocus::Hopus_pocus()
	: State_(this)
	, Hopus_pocusImageRenderer_(nullptr)
	, MonsterHitBox(nullptr)
	, MonsterBox(nullptr)
	, TimeCheck_(0.f)
	, Defeat_(false)
	, AniEnd_Intro_(false)
	, AniEnd_Attack_(false)
	, AniEnd_Death_Intro_(false)
	, AniEnd_Attack_End_(false)
	, FireCount_(0)


#ifdef _DEBUG
#endif // _DEBUG
{
}

Hopus_pocus::~Hopus_pocus() // default destructer µðÆúÆ® ¼Ò¸êÀÚ
{
}

void Hopus_pocus::Start()
{
	{
		Hopus_pocusImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		Hopus_pocusImageRenderer_->GetTransform()->SetLocalScaling({- 550.f, 825.f, 1.0f });
		Hopus_pocusImageRenderer_->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));

		Hopus_pocusImageRenderer_->CreateLevelAnimation("Hopus_pocus.png", "Hopus_pocus-Intro", 0, 17, 0.04f, false);
		Hopus_pocusImageRenderer_->CreateLevelAnimation("Hopus_pocus.png", "Hopus_pocus-Idle", 20, 36, 0.04f);
		Hopus_pocusImageRenderer_->CreateLevelAnimation("Hopus_pocus.png", "Hopus_pocus-Attack", 40, 56, 0.04f);
		Hopus_pocusImageRenderer_->CreateLevelAnimation("Hopus_pocus.png", "Hopus_pocus-Death", 109, 117, 0.04f);
		Hopus_pocusImageRenderer_->SetEndCallBack("Hopus_pocus-Intro", std::bind(&Hopus_pocus::AniEnd_Intro, this));
		Hopus_pocusImageRenderer_->SetEndCallBack("Hopus_pocus-Death", std::bind(&Hopus_pocus::AniEnd_Death_Intro, this));
		Hopus_pocusImageRenderer_->SetEndCallBack("Hopus_pocus-Attack", std::bind(&Hopus_pocus::AniEnd_Attack_End, this));
		Hopus_pocusImageRenderer_->SetFrameCallBack("Hopus_pocus-Attack", 49, std::bind(&Hopus_pocus::AniEnd_Attack, this));
		Hopus_pocusImageRenderer_->AnimationStop();
	}

	{
		MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBox->SetCollisionType(CollisionType::Rect);
		MonsterHitBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		MonsterHitBox->GetTransform()->SetLocalScaling(float4{ 350.f,625.f,1.f});
		MonsterHitBox->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));

		MonsterBox = CreateTransformComponent<GameEngineCollision>();
		MonsterBox->SetCollisionType(CollisionType::Rect);
		MonsterBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
		MonsterBox->GetTransform()->SetLocalScaling(float4{ 350.f,625.f,1.f});
		MonsterBox->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));
	}

	{
		State_.CreateState("Intro", &Hopus_pocus::Intro_Start, &Hopus_pocus::Intro_Update, &Hopus_pocus::Intro_End_);
		State_.CreateState("Idle", &Hopus_pocus::Idle_Start, &Hopus_pocus::Idle_Update, &Hopus_pocus::Idle_End_);
		State_.CreateState("Attack", &Hopus_pocus::Attack_Start, &Hopus_pocus::Attack_Update, &Hopus_pocus::Attack_End_);
		State_.CreateState("Defeat", &Hopus_pocus::Defeat_Start, &Hopus_pocus::Defeat_Update, &Hopus_pocus::Defeat_End_);

		State_.ChangeState("Intro");
	}

	//////////////½ºÅÝ
	{
		Hp_ = 100;
	}

}

void Hopus_pocus::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);

	State_.Update(_DeltaTime);
}

void Hopus_pocus::SpawnSmokeFx()
{
	Effect* Effect_ = GetLevel()->CreateActor<Effect>();
	Effect_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());

	int ran = Random_.RandomInt(0, 1);

	switch (ran)
	{
	case 0:
	{
		Effect_->EffectAnimationActor("Smoke_FX_Front.png", "Smoke_FX_Front1", float4{ 552.f,228.f }, 0, 11, 0.04f, false);
		//Effect_->EffectAnimationActor("Smoke_FX.png", "Smoke_FX_Back1", float4{ 552.f,228.f }, 40, 50, 0.04f, false);
		break;
	}
	case 1:
	{
		Effect_->EffectAnimationActor("Smoke_FX_Front.png", "Smoke_FX_Front2", float4{ 552.f,228.f }, 20, 36, 0.04f, false);
		//Effect_->EffectAnimationActor("Smoke_FX.png", "Smoke_FX_Back2", float4{ 552.f,228.f }, 60, 70, 0.04f, false);
		break;
	}
	}
}

void Hopus_pocus::Firefire()
{
	if (true == PossitionLeft_)
	{
		Wheezy_Fire* Fire = GetLevel()->CreateActor<Wheezy_Fire>();
		Fire->GetTransform()->SetWorldPosition(float4{ 850.f, -180.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });
		Fire->SetDir(false);
	}
	else
	{
		Wheezy_Fire* Fire = GetLevel()->CreateActor<Wheezy_Fire>();
		Fire->GetTransform()->SetWorldPosition(float4{ 430.f, -180.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });
		Fire->SetDir(true);
	}
}
