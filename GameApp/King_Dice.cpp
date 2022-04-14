#include "PreCompile.h"
#include "King_Dice.h"

King_Dice::King_Dice()
	: State_(this)
	, MonsterImageRenderer(nullptr)
	, MonsterHitBox(nullptr)
	, MonsterHitBoxHand(nullptr)
	
{
}

King_Dice::~King_Dice() // default destructer 디폴트 소멸자
{
}

void King_Dice::Start()
{
	{
		MonsterImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		MonsterImageRenderer->CreateAnimationFolder("KDIce-Idle", "KDIce-Idle", 0.04);
		MonsterImageRenderer->CreateAnimationFolder("KDIce-Intro", "KDIce-Intro", 0.04,false);
		MonsterImageRenderer->GetTransform()->SetLocalScaling({ 1440.f, 750.0f, 1.0f });
		MonsterImageRenderer->GetTransform()->SetLocalZPosition(static_cast<int>(ZOrder::Z01Actor03));

		MonsterImageRenderer->SetEndCallBack("KDIce-Intro",std::bind(&King_Dice::Idle,this));
	}

	{
		MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBox->SetCollisionType(CollisionType::Rect);
		MonsterHitBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		MonsterHitBox->GetTransform()->SetLocalScaling(float4{250.f,250.f,1.f});
		MonsterHitBox->GetTransform()->SetLocalPosition(float4{0.f,250.f,static_cast<int>(ZOrder::Z01Actor02)});
		MonsterHitBox->Off();

		MonsterHitBoxHand = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBoxHand->SetCollisionType(CollisionType::Rect);
		MonsterHitBoxHand->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		MonsterHitBoxHand->GetTransform()->SetLocalScaling(float4{ 150.f,250.f,1.f });
		MonsterHitBoxHand->Off();
		//MonsterHitBoxHand->GetTransform()->SetLocalPosition(float4{ 0.f,250.f,static_cast<int>(ZOrder::Z01Actor02) });
	}

	{
		State_.CreateState("Intro", &King_Dice::Intro_Start, &King_Dice::Intro_Update, &King_Dice::Intro_End_);
		State_.CreateState("Idle", &King_Dice::Idle_Start, &King_Dice::Idle_Update, &King_Dice::Idle_End_);
		State_.CreateState("Attack", &King_Dice::Attack_Start, &King_Dice::Attack_Update, &King_Dice::Attack_End_);
		State_.CreateState("Chop", &King_Dice::Chop_Start, &King_Dice::Chop_Update, &King_Dice::Chop_End_);
		State_.CreateState("Defeat", &King_Dice::Defeat_Start, &King_Dice::Defeat_Update, &King_Dice::Defeat_End_);
	}

	Intro();
}

void King_Dice::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);

	State_.Update(_DeltaTime);
}

void King_Dice::Intro()
{
	MonsterImageRenderer->SetChangeAnimation("KDIce-Intro");

	State_.ChangeState("Intro");
}

void King_Dice::Idle()
{
	MonsterImageRenderer->SetChangeAnimation("KDIce-Idle");

	State_.ChangeState("Idle");
}

void King_Dice::Attack()


{
}


