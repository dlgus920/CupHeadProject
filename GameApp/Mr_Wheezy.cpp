#include "PreCompile.h"
#include "Mr_Wheezy.h"
#include "Effect.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "PerryObjectDice.h"

Mr_Wheezy::Mr_Wheezy()
	: State_(this)
	, MonsterImageRenderer(nullptr)
	, MonsterHitBox(nullptr)
	, TimeCheck_(0.f)
	, Defeat_(false)
	, AniEnd_Intro_(false)
	, AniEnd_Attack_(false)
	, AniEnd_TellePort_In_(false)
	, AniEnd_TellePort_HB_(false)
	, AniEnd_TellePort_Out_(false)
	, AniEnd_Death_Intro_(false)
	, AniEnd_Attack_End_(false)
	, AshImageRenderer_Left_Front(nullptr)
	, AshImageRenderer_Right_Front(nullptr)
	, AshImageRenderer_Left_Back(nullptr)
	, AshImageRenderer_Right_Back(nullptr)


#ifdef _DEBUG
#endif // _DEBUG
{
}

Mr_Wheezy::~Mr_Wheezy() // default destructer µðÆúÆ® ¼Ò¸êÀÚ
{
}

void Mr_Wheezy::Start()
{
	{
		MonsterImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		MonsterImageRenderer->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Intro",0,17,0.04f,false);

		MonsterImageRenderer->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Idle",20,36,0.04f);

		MonsterImageRenderer->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Attack",40,56,0.04f);

		MonsterImageRenderer->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-TellePort-In",60,101,0.04f,false);
		MonsterImageRenderer->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-TellePort-Out",101,60,0.04f,false);

		MonsterImageRenderer->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Death-Intro",103,107,0.04f);
		MonsterImageRenderer->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Death-Idle",109,117,0.04f);

		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-Intro" ,std::bind(&Mr_Wheezy::AniEnd_Intro, this));
		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-TellePort-In" ,std::bind(&Mr_Wheezy::AniEnd_TellePort_In, this));
		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-TellePort-Out" ,std::bind(&Mr_Wheezy::AniEnd_TellePort_Out, this));
		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-Death-Intro", std::bind(&Mr_Wheezy::AniEnd_Death_Intro, this));
		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-Attack", std::bind(&Mr_Wheezy::AniEnd_Attack_End, this));

		MonsterImageRenderer->SetFrameCallBack("Mr_Wheezy-Attack", 49 ,std::bind(&Mr_Wheezy::AniEnd_Attack, this));

		MonsterImageRenderer->SetFrameCallBack("Mr_Wheezy-TellePort-In", 83 ,std::bind(&Mr_Wheezy::AniEnd_TellePort_HB_Off, this));
		MonsterImageRenderer->SetFrameCallBack("Mr_Wheezy-TellePort-Out", 83 ,std::bind(&Mr_Wheezy::AniEnd_TellePort_HB_On, this));

		MonsterImageRenderer->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
		MonsterImageRenderer->SetChangeAnimation("Mr_Wheezy-Idle");




		WheezyImageRenderer_Left_[0] = CreateTransformComponent<GameEngineImageRenderer>();
		WheezyImageRenderer_Left_[1] = CreateTransformComponent<GameEngineImageRenderer>();
		WheezyImageRenderer_Left_[2] = CreateTransformComponent<GameEngineImageRenderer>();
		WheezyImageRenderer_Right_[0] = CreateTransformComponent<GameEngineImageRenderer>();
		WheezyImageRenderer_Right_[1] = CreateTransformComponent<GameEngineImageRenderer>();
		WheezyImageRenderer_Right_[2] = CreateTransformComponent<GameEngineImageRenderer>();





	}

	{
		MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBox->SetCollisionType(CollisionType::Rect);
		MonsterHitBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		MonsterHitBox->GetTransform()->SetLocalScaling(float4{ 350.f,625.f,1.f});
		MonsterHitBox->GetTransform()->SetLocalPosition(float4{ 0.f,-200.f,1.f});
	}

	{
		State_.CreateState("Intro", &Mr_Wheezy::Intro_Start, &Mr_Wheezy::Intro_Update, &Mr_Wheezy::Intro_End_);
		State_.CreateState("Idle", &Mr_Wheezy::Idle_Start, &Mr_Wheezy::Idle_Update, &Mr_Wheezy::Idle_End_);
		State_.CreateState("Attack", &Mr_Wheezy::Attack_Start, &Mr_Wheezy::Attack_Update, &Mr_Wheezy::Attack_End_);
		State_.CreateState("Defeat", &Mr_Wheezy::Defeat_Start, &Mr_Wheezy::Defeat_Update, &Mr_Wheezy::Defeat_End_);
		State_.CreateState("Telleport", &Mr_Wheezy::Telleport_Start, &Mr_Wheezy::Telleport_Update, &Mr_Wheezy::Telleport_End_);

		State_.ChangeState("Intro");
	}

	//////////////½ºÅÝ
	{
		Hp_ = 100;
	}

}

void Mr_Wheezy::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);

	State_.Update(_DeltaTime);
}

void Mr_Wheezy::SetAshPale()
{
	AshImageRenderer_Left_Front = CreateTransformComponent<GameEngineImageRenderer>();
	AshImageRenderer_Left_Front->SetLevelImage("AshPaleFront.png");
	AshImageRenderer_Left_Front->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
	AshImageRenderer_Left_Front->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back04)));

	AshImageRenderer_Right_Front = CreateTransformComponent<GameEngineImageRenderer>();
	AshImageRenderer_Right_Front->SetLevelImage("AshPaleFront.png");
	AshImageRenderer_Right_Front->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
	AshImageRenderer_Right_Front->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back04)));

	AshImageRenderer_Left_Back = CreateTransformComponent<GameEngineImageRenderer>();
	AshImageRenderer_Left_Back->SetLevelImage("AshPaleBack.png");
	AshImageRenderer_Left_Back->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
	AshImageRenderer_Left_Back->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));

	AshImageRenderer_Right_Back = CreateTransformComponent<GameEngineImageRenderer>();
	AshImageRenderer_Right_Back->SetLevelImage("AshPaleBack.png");
	AshImageRenderer_Right_Back->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
	AshImageRenderer_Right_Back->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));
}

void Mr_Wheezy::SpawnSmokeFx()
{
	Effect* Effect_ = GetLevel()->CreateActor<Effect>();
	Effect_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());

	Effect_->EffectAnimationActor("Smoke_FX.png", "Smoke_FX_Front1", float4{ 552.f,228.f }, 0, 11, 0.04f, false);
	Effect_->EffectAnimationActor("Smoke_FX.png", "Smoke_FX_Front2", float4{ 552.f,228.f }, 20, 36, 0.04f, false);

	Effect_->EffectAnimationActor("Smoke_FX.png", "Smoke_FX_Back1", float4{ 552.f,228.f }, 40, 50, 0.04f, false);
	Effect_->EffectAnimationActor("Smoke_FX.png", "Smoke_FX_Back2", float4{ 552.f,228.f }, 60, 70, 0.04f, false);
}
