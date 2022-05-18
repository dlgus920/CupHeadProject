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
	, AniEnd_Idle_(false)
	, AniEnd_Intro_(false)
	, AniEnd_Attack_(false)
	, AniEnd_Attack_End_(false)


#ifdef _DEBUG
#endif // _DEBUG
{
}

Hopus_pocus::~Hopus_pocus() // default destructer µðÆúÆ® ¼Ò¸êÀÚ
{
}

void Hopus_pocus::Start()
{
	GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));

	{
		Hopus_pocusImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();

		Hopus_pocusImageRenderer_->GetTransform()->SetLocalScaling(float4{ 800.f,740.f });
		//Hopus_pocusImageRenderer_->GetTransform()->SetLocalScaling({620.f, 740.f, 1.0f });
		//Hopus_pocusImageRenderer_->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));

		Hopus_pocusImageRenderer_->CreateLevelAnimationFolder("Hopus_Pocus_Intro","Hopus_Pocus-Intro",0.04f);
		Hopus_pocusImageRenderer_->CreateLevelAnimationFolder("Hopus_Pocus_Attack","Hopus_Pocus-Attack",0.04f);
		Hopus_pocusImageRenderer_->CreateLevelAnimationFolder("Hopus_Pocus_Idle","Hopus_Pocus-Idle",0.04f);
		Hopus_pocusImageRenderer_->CreateLevelAnimationFolder("Hopus_Pocus_Death","Hopus_Pocus-Death",0.04f);

		Hopus_pocusImageRenderer_->SetEndCallBack("Hopus_Pocus-Intro", std::bind(&Hopus_pocus::AniEnd_Intro, this));
		Hopus_pocusImageRenderer_->SetEndCallBack("Hopus_Pocus-Attack", std::bind(&Hopus_pocus::AniEnd_Attack_End, this));
		Hopus_pocusImageRenderer_->SetFrameCallBack("Hopus_Pocus-Attack", 24,std::bind(&Hopus_pocus::AniEnd_Attack, this));
		Hopus_pocusImageRenderer_->SetEndCallBack("Hopus_Pocus-Idle", std::bind(&Hopus_pocus::AniEnd_Idle, this));
	}

	{
		MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBox->SetCollisionType(CollisionType::Rect);
		MonsterHitBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		MonsterHitBox->GetTransform()->SetLocalScaling(float4{ 640.f,740.f });

		MonsterBox = CreateTransformComponent<GameEngineCollision>();
		MonsterBox->SetCollisionType(CollisionType::Rect);
		MonsterBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
		MonsterBox->GetTransform()->SetLocalScaling(float4{ 640.f,740.f });
	}

	{
		State_.CreateState("Intro", &Hopus_pocus::Intro_Start, &Hopus_pocus::Intro_Update, &Hopus_pocus::Intro_End);
		State_.CreateState("Idle", &Hopus_pocus::Idle_Start, &Hopus_pocus::Idle_Update, &Hopus_pocus::Idle_End);
		State_.CreateState("Attack", &Hopus_pocus::Attack_Start, &Hopus_pocus::Attack_Update, &Hopus_pocus::Attack_End);
		State_.CreateState("Defeat", &Hopus_pocus::Defeat_Start, &Hopus_pocus::Defeat_Update, &Hopus_pocus::Defeat_End);

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
	//if (true == PossitionLeft_)
	//{
	//	Wheezy_Fire* Fire = GetLevel()->CreateActor<Wheezy_Fire>();
	//	Fire->GetTransform()->SetWorldPosition(float4{ 850.f, -180.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });
	//	Fire->SetDir(false);
	//}
	//else
	//{
	//	Wheezy_Fire* Fire = GetLevel()->CreateActor<Wheezy_Fire>();
	//	Fire->GetTransform()->SetWorldPosition(float4{ 430.f, -180.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });
	//	Fire->SetDir(true);
	//}
}


void Hopus_pocus::AniEnd_Intro()
{
	AniEnd_Intro_ = true;
	Hopus_pocusImageRenderer_->GetTransform()->SetLocalScaling(float4{ 640.f,740.f });
	Hopus_pocusImageRenderer_->GetTransform()->SetWorldMove(float4{ -90.f,0.f });
}