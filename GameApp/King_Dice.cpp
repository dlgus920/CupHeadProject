#include "PreCompile.h"
#include "King_Dice.h"

King_Dice::King_Dice()
	: State_(this)
	, BattleState_(this)
	, MonsterImageRenderer(nullptr)
	, MonsterHitBox(nullptr)
	, MonsterHitBoxHand(nullptr)
	, TimeCheck_(0.f)
	, CardCount_(0)
	
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

		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Birth", "KDice-Attack-Body-Birth", 0.04,false);
		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Birth", "KDice-Attack-Body-End", 0.04,false);
		MonsterImageRenderer->SetAnimationReverse("KDice-Attack-Body-End");

		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Idle", "KDice-Attack-Body-Idle", 0.04);

		MonsterImageRenderer->GetTransform()->SetLocalScaling({ 1440.f, 750.0f, 1.0f });
		MonsterImageRenderer->GetTransform()->SetLocalZPosition(static_cast<int>(ZOrder::Z01Actor03));
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

		BattleState_.CreateState("BattleState_Battle",&King_Dice::BattleState_Battle_Start,&King_Dice::BattleState_Battle_Update,&King_Dice::BattleState_Battle_End);
		BattleState_.CreateState("BattleState_Dice",&King_Dice::BattleState_Dice_Start,&King_Dice::BattleState_Dice_Update,&King_Dice::BattleState_Dice_End);
	}

	{
		Hand_.ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();

		Hand_.Collision = CreateTransformComponent<GameEngineCollision>();
		Hand_.Collision->SetCollisionType(CollisionType::Rect);
		Hand_.Collision->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);

		Hand_.ImageRenderer->CreateAnimationFolder("KDice-Attack-Hand-Birth", "KDice-Attack-Hand-Birth", 0.04);
		//Hand_.ImageRenderer->CreateAnimationFolder("KDice-Attack-Hand-Birth", "KDice-Attack-Hand-End", 0.04);
		//Hand_.ImageRenderer->SetAnimationReverse("KDice-Attack-Hand-End");



		Hand_.ImageRenderer->CreateAnimationFolder("KDice-Attack-Hand-Idle", "KDice-Attack-Hand-Idle", 0.04);

		Hand_.HandSetLocalPosition(float4{ -500.f ,-650.f, 1.f });

		Hand_.ImageRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,650.f, 1.f });
		Hand_.Collision->GetTransform()->SetLocalScaling(float4{ 500.f,650.f, 1.f });

		Hand_.HandOff();
	}
#ifndef _DEBUG
	Hand_.ImageRenderer->SetEndCallBack("KDice-Attack-Hand-Birth", std::bind(&King_Dice::Hand::, &Hand_));
	Hand_.ImageRenderer->SetEndCallBack("KDice-Attack-Hand-End", std::bind(&King_Dice::Hand::, &Hand_));

	MonsterImageRenderer->SetEndCallBack("KDIce-Intro", std::bind(&King_Dice::Idle, this));
	MonsterImageRenderer->SetEndCallBack("KDice-Attack-Body-Birth", std::bind(&King_Dice::, this));
	MonsterImageRenderer->SetEndCallBack("KDice-Attack-Body-End", std::bind(&King_Dice::, this));
#endif // !_DEBUG

	Intro();
}

void King_Dice::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);

	State_.Update(_DeltaTime);
}

void King_Dice::Intro()
{
	State_.ChangeState("Intro");
}

void King_Dice::Idle()
{
	State_.ChangeState("Idle");
}

void King_Dice::Attack()
{
	State_.ChangeState("Attack");
}

void King_Dice::HandBirth()
{
}

void King_Dice::HandIdle()
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Idle");

	Hand_.HandOn();
	Hand_.HandBirth();
}
