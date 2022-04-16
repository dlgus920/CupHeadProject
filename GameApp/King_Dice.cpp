#include "PreCompile.h"
#include "King_Dice.h"

#include <GameEngineBase/GameEngineRandom.h>

King_Dice::King_Dice()
	: State_(this)
	, BattleState_(this)
	, MonsterImageRenderer(nullptr)
	, MonsterHitBox(nullptr)
	, MonsterHitBoxHand(nullptr)
	, IsDiceTime_(true)
	, TimeCheck_(0.f)
	, CardCount_(0)
	, AniEnd_Intro_(false)
	, AniEnd_Attack_Body_Birth_(false)
	, AniEnd_Attack_Body_End_(false)
	, AniEnd_Attack_Hand_Birth_(false)
{
}

King_Dice::~King_Dice() // default destructer ����Ʈ �Ҹ���
{
}

void King_Dice::Start()
{
	{
		MonsterImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		MonsterImageRenderer->CreateAnimationFolder("KDIce-Idle", "KDIce-Idle", 0.04f);
		MonsterImageRenderer->CreateAnimationFolder("KDIce-Intro", "KDIce-Intro", 0.04f, false);

		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Birth", "KDice-Attack-Body-Birth", 0.04f, false);
		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Birth", "KDice-Attack-Body-End", 0.04f, false);
		MonsterImageRenderer->SetAnimationReverse("KDice-Attack-Body-End");

		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Idle", "KDice-Attack-Body-Idle", 0.04f);

		MonsterImageRenderer->SetEndCallBack("KDIce-Intro", std::bind(&King_Dice::AniEnd_Intro, this));
		MonsterImageRenderer->SetEndCallBack("KDice-Attack-Body-Birth", std::bind(&King_Dice::AniEnd_Attack_Body_Birth, this));
		MonsterImageRenderer->SetEndCallBack("KDice-Attack-Body-End", std::bind(&King_Dice::AniEnd_Attack_Body_End, this));

		MonsterImageRenderer->GetTransform()->SetLocalScaling({ 1440.f, 750.0f, 1.0f });
		MonsterImageRenderer->GetTransform()->SetLocalZPosition(static_cast<int>(ZOrder::Z01Actor03));

		Hand_.ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		Hand_.ImageRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,650.f, 1.f });
		Hand_.ImageRenderer->GetTransform()->SetLocalPosition(float4{ -310.f, 38.f, static_cast<int>(ZOrder::Z01Actor04) });

		Hand_.ImageRenderer->CreateAnimationFolder("KDice-Attack-Hand-Birth", "KDice-Attack-Hand-Birth", 0.04f, false);
		Hand_.ImageRenderer->CreateAnimationFolder("KDice-Attack-Hand-Idle", "KDice-Attack-Hand-Idle", 0.04f, true);

		Hand_.ImageRenderer->SetEndCallBack("KDice-Attack-Hand-Birth", std::bind(&King_Dice::AniEnd_Attack_Hand_Birth, this));
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

		Hand_.Collision = CreateTransformComponent<GameEngineCollision>();
		Hand_.Collision->SetCollisionType(CollisionType::Rect);
		Hand_.Collision->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		Hand_.Collision->GetTransform()->SetLocalScaling(float4{ 200.f,400.f, 1.f });
		Hand_.Collision->GetTransform()->SetLocalPosition(float4{ -410.f, -100.f, static_cast<int>(ZOrder::Z01Actor04) });

		HandLeft();
		Hand_.HandOff();
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

	BattleState_.ChangeState("BattleState_Dice");
	State_.ChangeState("Intro");

	Cardvector_.reserve(20);
}

void King_Dice::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(Hand_.Collision->GetTransform(), CollisionType::Rect);

	BattleState_.Update(_DeltaTime);
	State_.Update(_DeltaTime);
}

void King_Dice::Intro()
{
}

void King_Dice::Idle()
{
	State_.ChangeState("Idle");
}

void King_Dice::Attack()
{
	State_.ChangeState("Attack");
}

void King_Dice::HandSwitching()
{
	GameEngineRandom Ranint;

	Hand_Dir _Hand_Dir = static_cast<Hand_Dir>(Ranint.RandomInt(0, 1));
	Hand_.Hand_Dir_ = static_cast<Hand_Dir>(Ranint.RandomInt(0, 1));

	if (Hand_.Hand_Dir_ == Hand_Dir::Right)
	{
		HandRight();
	}
	else if (Hand_.Hand_Dir_ == Hand_Dir::Left)
	{
		HandLeft();
	}
}

void King_Dice::HandRight()
{
	Hand_.ImageRenderer->GetTransform()->SetLocalPosition(float4{ 310.f, 38.f, static_cast<int>(ZOrder::Z01Actor04) });
	Hand_.Collision->GetTransform()->SetLocalPosition(float4{ 410.f, -100.f, static_cast<int>(ZOrder::Z01Actor04) });

	Hand_.ImageRenderer->GetTransform()->SetLocalScaling(float4{ -500.f,650.f, 1.f });
	MonsterImageRenderer->GetTransform()->SetLocalScaling({ -1440.f, 750.0f, 1.0f });
	//ImageRenderer->GetTransform()->SetHorizenInvertTransform();
}

void King_Dice::HandLeft()
{
	Hand_.ImageRenderer->GetTransform()->SetLocalPosition(float4{ -310.f, 38.f, static_cast<int>(ZOrder::Z01Actor04) });
	Hand_.Collision->GetTransform()->SetLocalPosition(float4{ -410.f, -100.f, static_cast<int>(ZOrder::Z01Actor04) });

	Hand_.ImageRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,650.f, 1.f });
	MonsterImageRenderer->GetTransform()->SetLocalScaling({ 1440.f, 750.0f, 1.0f });
	//ImageRenderer->GetTransform()->SetHorizenInvertTransform();
}
void King_Dice::HandBirth()
{
}

void King_Dice::HandIdle()
{
	MonsterImageRenderer->SetChangeAnimation("KDice-Attack-Body-Idle");

	Hand_.HandOn();
}

void King_Dice::SpawnCard()
{
	Card _Card;
	_Card.ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	_Card.Collision = CreateTransformComponent<GameEngineCollision>();


	_Card.ImageRenderer->CreateAnimation("Card_Club.png", "Card_Club", 0, 20, 0.04f);
	_Card.ImageRenderer->SetChangeAnimation("Card_Club");

	_Card.ImageRenderer->GetTransform()->SetLocalScaling(float4{ 230.f,240.f, 1.f });
	_Card.Collision->GetTransform()->SetLocalScaling(float4{ 230.f,240.f, 1.f });

	if (Hand_.Hand_Dir_ == Hand_Dir::Left)
	{
		_Card.ImageRenderer->GetTransform()->SetLocalPosition(float4{ -410.f, -150.f, static_cast<int>(ZOrder::Z01Actor04) });
		_Card.Collision->GetTransform()->SetLocalPosition(float4{ -410.f, -150.f, static_cast<int>(ZOrder::Z01Actor04) });
		_Card.ImageRenderer->GetTransform()->SetLocalScaling(float4{ 230.f,240.f, 1.f });
	}
	else if (Hand_.Hand_Dir_ == Hand_Dir::Right)
	{
		_Card.ImageRenderer->GetTransform()->SetLocalPosition(float4{ 410.f, -150.f, static_cast<int>(ZOrder::Z01Actor04) });
		_Card.Collision->GetTransform()->SetLocalPosition(float4{ 410.f, -150.f, static_cast<int>(ZOrder::Z01Actor04) });
		_Card.ImageRenderer->GetTransform()->SetLocalScaling(float4{ -230.f,240.f, 1.f });
	}
	_Card.Collision->GetTransform()->SetLocalScaling(float4{ 230.f,240.f, 1.f });

	Cardvector_.push_back(_Card);
}

void King_Dice::CardUpdate(float _DeltaTime)
{
	float4 MovePos;

	if (Hand_.Hand_Dir_ == Hand_Dir::Left)
	{
		MovePos= float4{ 400.f * _DeltaTime,0.f,0.f };
	}
	else if (Hand_.Hand_Dir_ == Hand_Dir::Right)
	{
		MovePos = float4{ -400.f * _DeltaTime,0.f,0.f };
	}

	for (int i = 0; i < Cardvector_.size(); ++i)
	{
		Cardvector_[i].CardMove(MovePos);
		GetLevel()->PushDebugRender(Cardvector_[i].Collision->GetTransform(), CollisionType::Rect);
	}

}

void King_Dice::CardClear()
{
	for (int i = 0; i < Cardvector_.size(); ++i)
	{
		Cardvector_[i].ImageRenderer->Death();
		Cardvector_[i].Collision->Death();
	}

	Cardvector_.clear();
}

King_Dice::Card::Card()
	: Collision(nullptr)
	, ImageRenderer(nullptr)
{
}

King_Dice::Card::~Card()
{
}

void King_Dice::Card::CardMove(float4 Move)
{
	ImageRenderer->GetTransform()->SetLocalMove(Move);
	Collision->GetTransform()->SetLocalMove(Move);
}

King_Dice::Hand::Hand()
	: Collision(nullptr)
	, ImageRenderer(nullptr)
	, IsAttacking_(false)
	, Hand_Dir_(Hand_Dir::Left)
{
}

King_Dice::Hand::~Hand()
{
}

void King_Dice::Hand::HandSetHorizenInvertTransform()
{
	ImageRenderer->GetTransform()->SetHorizenInvertTransform();
}

void King_Dice::Hand::HandOff()
{
	Collision->Off();
	ImageRenderer->Off();
	IsAttacking_ = false;
}

void King_Dice::Hand::HandOn()
{
	Collision->On();
	ImageRenderer->On();
}

void King_Dice::Hand::HandIdle()
{
	ImageRenderer->SetChangeAnimation("KDice-Attack-Hand-Idle");
	IsAttacking_ = true;
}

void King_Dice::Hand::HandEnd()
{
	ImageRenderer->SetChangeAnimation("KDice-Attack-Hand-End");
	IsAttacking_ = false;
}

void King_Dice::Hand::HandBirth()
{
	ImageRenderer->SetChangeAnimation("KDice-Attack-Hand-Birth");
}
