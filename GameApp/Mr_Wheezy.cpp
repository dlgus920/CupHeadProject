#include "PreCompile.h"
#include "Mr_Wheezy.h"
#include "Effect.h"
#include "Wheezy_Fire.h"
#include "UserGame.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Mr_Wheezy::Mr_Wheezy()
	: State_(this)
	, WheezyImageRenderer_Left_(nullptr)
	, WheezyImageRenderer_Right_(nullptr)
	, AshImageRenderer_Left_Front(nullptr)
	, AshImageRenderer_Right_Front(nullptr)
	, AshImageRenderer_Left_Back(nullptr)
	, AshImageRenderer_Right_Back(nullptr)
	, Cur_WheezyImageRenderer_(nullptr)
	, MonsterHitBox(nullptr)
	, MonsterBox(nullptr)
	, TimeCheck_(0.f)
	, Defeat_(false)
	, AniEnd_Intro_(false)
	, AniEnd_Attack_(false)
	, AniEnd_TellePort_In_(false)
	, AniEnd_TellePort_HB_(false)
	, AniEnd_TellePort_Out_(false)
	, AniEnd_Death_Intro_(false)
	, AniEnd_Attack_End_(false)
	, PossitionLeft_(true)
	, FireCount_(0)


#ifdef _DEBUG
#endif // _DEBUG
{
}

Mr_Wheezy::~Mr_Wheezy() // default destructer 디폴트 소멸자
{
}

void Mr_Wheezy::Start()
{
	{
		WheezyImageRenderer_Left_ = CreateTransformComponent<GameEngineImageRenderer>();
		WheezyImageRenderer_Left_->GetTransform()->SetLocalScaling({- 550.f, 825.f, 1.0f });
		WheezyImageRenderer_Left_->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));

		WheezyImageRenderer_Left_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Intro", 0, 17, 0.04f, false);
		//TODO: 일정 프레임을 반복시키다가, IntroENd시 쭉 재생
		WheezyImageRenderer_Left_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Idle", 20, 36, 0.04f);
		WheezyImageRenderer_Left_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Attack", 40, 56, 0.04f);
		WheezyImageRenderer_Left_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-TellePort-In", 60, 101, 0.04f, false);
		WheezyImageRenderer_Left_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-TellePort-Out", 101, 60, 0.04f, false);
		WheezyImageRenderer_Left_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Death-Intro", 103, 107, 0.04f);
		WheezyImageRenderer_Left_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Death-Idle", 109, 117, 0.04f);
		WheezyImageRenderer_Left_->SetEndCallBack("Mr_Wheezy-Intro", std::bind(&Mr_Wheezy::AniEnd_Intro, this));
		WheezyImageRenderer_Left_->SetEndCallBack("Mr_Wheezy-TellePort-In", std::bind(&Mr_Wheezy::AniEnd_TellePort_In, this));
		WheezyImageRenderer_Left_->SetEndCallBack("Mr_Wheezy-TellePort-Out", std::bind(&Mr_Wheezy::AniEnd_TellePort_Out, this));
		WheezyImageRenderer_Left_->SetEndCallBack("Mr_Wheezy-Death-Intro", std::bind(&Mr_Wheezy::AniEnd_Death_Intro, this));
		WheezyImageRenderer_Left_->SetEndCallBack("Mr_Wheezy-Attack", std::bind(&Mr_Wheezy::AniEnd_Attack_End, this));
		WheezyImageRenderer_Left_->SetFrameCallBack("Mr_Wheezy-Attack", 49, std::bind(&Mr_Wheezy::AniEnd_Attack, this));
		WheezyImageRenderer_Left_->SetFrameCallBack("Mr_Wheezy-TellePort-In", 83, std::bind(&Mr_Wheezy::AniEnd_TellePort_HB_On, this));
		WheezyImageRenderer_Left_->SetFrameCallBack("Mr_Wheezy-TellePort-Out", 83, std::bind(&Mr_Wheezy::AniEnd_TellePort_HB_On, this));
		WheezyImageRenderer_Left_->SetChangeAnimation("Mr_Wheezy-TellePort-Out");
		WheezyImageRenderer_Left_->AnimationStop();
	}

	{
		WheezyImageRenderer_Right_ = CreateTransformComponent<GameEngineImageRenderer>();
		WheezyImageRenderer_Right_->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
		WheezyImageRenderer_Right_->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back06)));

		WheezyImageRenderer_Right_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Intro", 0, 17, 0.05555f, false);
		WheezyImageRenderer_Right_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Idle", 20, 36, 0.04f);
		WheezyImageRenderer_Right_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Attack", 40, 56, 0.04f);
		WheezyImageRenderer_Right_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-TellePort-In", 60, 101, 0.04f, false);
		WheezyImageRenderer_Right_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-TellePort-Out", 101, 60, 0.04f, false);
		WheezyImageRenderer_Right_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Death-Intro", 103, 107, 0.04f);
		WheezyImageRenderer_Right_->CreateLevelAnimation("Mr_Wheezy.png", "Mr_Wheezy-Death-Idle", 109, 117, 0.04f);
		WheezyImageRenderer_Right_->SetEndCallBack("Mr_Wheezy-Intro", std::bind(&Mr_Wheezy::AniEnd_Intro, this));
		WheezyImageRenderer_Right_->SetEndCallBack("Mr_Wheezy-TellePort-In", std::bind(&Mr_Wheezy::AniEnd_TellePort_In, this));
		WheezyImageRenderer_Right_->SetEndCallBack("Mr_Wheezy-TellePort-Out", std::bind(&Mr_Wheezy::AniEnd_TellePort_Out, this));
		WheezyImageRenderer_Right_->SetEndCallBack("Mr_Wheezy-Death-Intro", std::bind(&Mr_Wheezy::AniEnd_Death_Intro, this));
		WheezyImageRenderer_Right_->SetEndCallBack("Mr_Wheezy-Attack", std::bind(&Mr_Wheezy::AniEnd_Attack_End, this));
		WheezyImageRenderer_Right_->SetFrameCallBack("Mr_Wheezy-Attack", 49, std::bind(&Mr_Wheezy::AniEnd_Attack, this));
		WheezyImageRenderer_Right_->SetFrameCallBack("Mr_Wheezy-Death-Intro", 106, std::bind(&Mr_Wheezy::AniEnd_Death_4, this));
		WheezyImageRenderer_Right_->SetFrameCallBack("Mr_Wheezy-TellePort-In", 83, std::bind(&Mr_Wheezy::AniEnd_TellePort_HB_On, this));
		WheezyImageRenderer_Right_->SetFrameCallBack("Mr_Wheezy-TellePort-Out", 83, std::bind(&Mr_Wheezy::AniEnd_TellePort_HB_On, this));
		WheezyImageRenderer_Right_->SetChangeAnimation("Mr_Wheezy-Idle");

		Cur_WheezyImageRenderer_ = WheezyImageRenderer_Right_;
	}

	{
		AshImageRenderer_Left_Front = CreateTransformComponent<GameEngineImageRenderer>();
		AshImageRenderer_Left_Front->GetTransform()->SetLocalScaling({ -550.f, 825.f, 1.0f });
		AshImageRenderer_Left_Front->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back04)));
		AshImageRenderer_Left_Front->SetLevelImage("AshPaleFront.png");

		AshImageRenderer_Left_Back = CreateTransformComponent<GameEngineImageRenderer>();
		AshImageRenderer_Left_Back->GetTransform()->SetLocalScaling({- 550.f, 825.f, 1.0f });
		AshImageRenderer_Left_Back->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back07)));
		AshImageRenderer_Left_Back->SetLevelImage("AshPaleBack.png");

		AshImageRenderer_Right_Front = CreateTransformComponent<GameEngineImageRenderer>();
		AshImageRenderer_Right_Front->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
		AshImageRenderer_Right_Front->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back04)));
		AshImageRenderer_Right_Front->SetLevelImage("AshPaleFront.png");

		AshImageRenderer_Right_Back = CreateTransformComponent<GameEngineImageRenderer>();
		AshImageRenderer_Right_Back->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
		AshImageRenderer_Right_Back->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back07)));
		AshImageRenderer_Right_Back->SetLevelImage("AshPaleBack.png");
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
		State_.CreateState("Intro", &Mr_Wheezy::Intro_Start, &Mr_Wheezy::Intro_Update, &Mr_Wheezy::Intro_End_);
		State_.CreateState("Idle", &Mr_Wheezy::Idle_Start, &Mr_Wheezy::Idle_Update, &Mr_Wheezy::Idle_End_);
		State_.CreateState("Attack", &Mr_Wheezy::Attack_Start, &Mr_Wheezy::Attack_Update, &Mr_Wheezy::Attack_End_);
		State_.CreateState("Defeat", &Mr_Wheezy::Defeat_Start, &Mr_Wheezy::Defeat_Update, &Mr_Wheezy::Defeat_End_);
		State_.CreateState("Telleport", &Mr_Wheezy::Telleport_Start, &Mr_Wheezy::Telleport_Update, &Mr_Wheezy::Telleport_End_);

		State_.ChangeState("Intro");
	}

	//////////////스텟
	{
		Hp_ = 100;
	}

}

void Mr_Wheezy::Update(float _DeltaTime)
{
	if (true == UserGame::StageInfo_.Debug_)
	{
		if (true == MonsterHitBox->IsUpdate())
		{
			GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);
		}
	}

	State_.Update(_DeltaTime);
}

void Mr_Wheezy::ChangeCurRenderer()
{
	if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Left_)
	{
		WheezyImageRenderer_Right_->AnimationPlay();
		WheezyImageRenderer_Left_->AnimationStop();

		Cur_WheezyImageRenderer_->AnimationStop();

		Cur_WheezyImageRenderer_ = WheezyImageRenderer_Right_;
	}

	else if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Right_)
	{
		Cur_WheezyImageRenderer_ = WheezyImageRenderer_Left_;
	}

	else
	{
		GameEngineDebug::MsgBoxError("Cur_WheezyImageRenderer_가 null임");
	}
}

void Mr_Wheezy::ChangeAshImageRenderer()
{
	if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Left_)
	{
		Cur_WheezyImageRenderer_ = WheezyImageRenderer_Right_;
	}

	else if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Right_)
	{
		Cur_WheezyImageRenderer_ = WheezyImageRenderer_Left_;
	}

	else
	{
		GameEngineDebug::MsgBoxError("Cur_WheezyImageRenderer_가 null임");
	}
}

void Mr_Wheezy::MoveHitBox()
{
	if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Left_)
	{
		MonsterHitBox->GetTransform()->SetWorldPosition(float4(240.f, -80.f));
	}

	else if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Right_)
	{
		MonsterHitBox->GetTransform()->SetWorldPosition(float4(1040.f, -80.f));
	}

	else
	{
		GameEngineDebug::MsgBoxError("Cur_WheezyImageRenderer_가 null임");
	}
}

void Mr_Wheezy::SpawnSmokeFx()
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

void Mr_Wheezy::Firefire()
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

void Mr_Wheezy::AniEnd_Death_4()
{
	if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Left_)
	{		
		WheezyImageRenderer_Left_->	GetTransform()
			->SetWorldPosition(float4(340.f, -190.f, static_cast<float>(ZOrder::Z02Back02_5)));
	}
	else if (Cur_WheezyImageRenderer_ == WheezyImageRenderer_Right_)
	{
		WheezyImageRenderer_Right_->GetTransform()
			->SetWorldPosition(float4(940.f, -190.f, static_cast<float>(ZOrder::Z02Back02_5)));
	}
}
