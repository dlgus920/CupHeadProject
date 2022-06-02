#include "PreCompile.h"
#include "Hopus_pocus.h"
#include "Effect.h"

#include "Hopus_Bullet.h"
#include "Hopus_Trumps.h"
#include "Player.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineSoundManager.h>
#include <GameEngine/GameEngineSoundPlayer.h>

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
	, Houpus_AIPattern_(false)


#ifdef _DEBUG
#endif // _DEBUG
{
}

Hopus_pocus::~Hopus_pocus() // default destructer 디폴트 소멸자
{
}

void Hopus_pocus::Start()
{
	{
		Hopus_pocusImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();

		Hopus_pocusImageRenderer_->GetTransform()->SetLocalScaling(float4{ 800.f,740.f });

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
		MonsterHitBox->GetTransform()->SetLocalScaling(float4{ 240.f,590.f });
		MonsterHitBox->GetTransform()->SetLocalPosition(float4{ -50.f,-50.f });

		MonsterBox = CreateTransformComponent<GameEngineCollision>();
		MonsterBox->SetCollisionType(CollisionType::Rect);
		MonsterBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
		MonsterBox->GetTransform()->SetLocalScaling(float4{ 240.f,590.f });
		MonsterBox->GetTransform()->SetLocalPosition(float4{ -50.f,-50.f });
	}

	{
		State_.CreateState("Intro", &Hopus_pocus::Intro_Start, &Hopus_pocus::Intro_Update, &Hopus_pocus::Intro_End);
		State_.CreateState("Idle", &Hopus_pocus::Idle_Start, &Hopus_pocus::Idle_Update, &Hopus_pocus::Idle_End);
		State_.CreateState("Attack", &Hopus_pocus::Attack_Start, &Hopus_pocus::Attack_Update, &Hopus_pocus::Attack_End);
		State_.CreateState("Defeat", &Hopus_pocus::Defeat_Start, &Hopus_pocus::Defeat_Update, &Hopus_pocus::Defeat_End);

		State_.ChangeState("Intro");
	}

	Hopus_Bullet_ = GetLevel()->CreateActor<Hopus_Bullet>(); // 미리 만들어두고 필요할때마다 리셋함
	Hopus_Bullet_->GetTransform()->SetWorldPosition(float4{640.f,-320.f,static_cast<float>(ZOrder::Z01Actor01Bullet01)});

	Hopus_Trumps_ = GetLevel()->CreateActor<Hopus_Trumps>(); // 미리 만들어두고 필요할때마다 리셋함
	Hopus_Trumps_->GetTransform()->SetWorldPosition(float4{ 640.f,-320.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });

	//////////////스텟
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
}

void Hopus_pocus::Fire()
{
	if (true == Houpus_AIPattern_)
	{
		Hopus_Bullet_->AttackStart();
	}
	else
	{
		Hopus_Trumps_->AttackStart();
	}
}

void Hopus_pocus::FireReady()
{
	if (true == Houpus_AIPattern_)
	{
		Hopus_Bullet_->Reset(Player::MainPlayer->GetTransform()->GetWorldPosition());
	}
	else
	{
		Hopus_Trumps_->Reset();
	}
}

void Hopus_pocus::AniEnd_Intro()
{
	AniEnd_Intro_ = true;
	Hopus_pocusImageRenderer_->GetTransform()->SetLocalScaling(float4{ 640.f,740.f });
	Hopus_pocusImageRenderer_->GetTransform()->SetWorldMove(float4{ -90.f,0.f });
}