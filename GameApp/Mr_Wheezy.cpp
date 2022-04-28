#include "PreCompile.h"
#include "Mr_Wheezy.h"
#include "Effect.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "PerryObjectDice.h"

Mr_Wheezy::Mr_Wheezy()
	: State_(this)
	, BattleState_(this)
	, MonsterImageRenderer(nullptr)
	, MonsterHitBox(nullptr)
	, TimeCheck_(0.f)
#ifdef _DEBUG
	, AniEnd_Intro_(false)
	, AniEnd_Attack_Body_Birth_(false)
	, AniEnd_Attack_Body_End_(false)
	, AniEnd_Attack_Hand_Birth_(false)
#endif // _DEBUG
	, AniEnd_Clap_Dice_(false)
	, AniEnd_Clap_(false)
	, Defeat_(false)
{
}

Mr_Wheezy::~Mr_Wheezy() // default destructer µðÆúÆ® ¼Ò¸êÀÚ
{
}

void Mr_Wheezy::Start()
{
	{
		MonsterImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		MonsterImageRenderer->CreateAnimationFolder("KDIce-Idle", "KDIce-Idle", 0.04f);
		MonsterImageRenderer->CreateAnimationFolder("KDIce-Intro", "KDIce-Intro", 0.04f, false);
		MonsterImageRenderer->CreateAnimationFolder("KDice-Defeat", "KDice-Defeat", 0.04f, true);

		MonsterImageRenderer->CreateAnimationFolder("KDice-Chomp", "KDice-Chomp", 0.04f, false);

		MonsterImageRenderer->CreateAnimationFolder("KDice-Clap", "KDice-Clap", 0.04f, false);
		MonsterImageRenderer->SetFrameCallBack("KDice-Clap", 26 ,std::bind(&Mr_Wheezy::AniEnd_Clap_Dice, this));
		MonsterImageRenderer->SetEndCallBack("KDice-Clap" ,std::bind(&Mr_Wheezy::AniEnd_Clap, this));

		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Birth", "KDice-Attack-Body-Birth", 0.04f, false);
		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Birth", "KDice-Attack-Body-End", 0.04f, false);
		MonsterImageRenderer->SetAnimationReverse("KDice-Attack-Body-End");

		MonsterImageRenderer->CreateAnimationFolder("KDice-Attack-Body-Idle", "KDice-Attack-Body-Idle", 0.04f);

		MonsterImageRenderer->SetEndCallBack("KDIce-Intro", std::bind(&Mr_Wheezy::AniEnd_Intro, this));
		MonsterImageRenderer->SetEndCallBack("KDice-Attack-Body-Birth", std::bind(&Mr_Wheezy::AniEnd_Attack_Body_Birth, this));
		MonsterImageRenderer->SetEndCallBack("KDice-Attack-Body-End", std::bind(&Mr_Wheezy::AniEnd_Attack_Body_End, this));

		MonsterImageRenderer->GetTransform()->SetLocalScaling({ 1440.f, 750.0f, 1.0f });
		MonsterImageRenderer->GetTransform()->SetLocalPosition(float4(0.f, 0.f, static_cast<float>(ZOrder::Z01Actor03)));
	}

	{
		MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBox->SetCollisionType(CollisionType::Rect);
		MonsterHitBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		MonsterHitBox->GetTransform()->SetLocalScaling(float4{250.f,250.f,1.f});
		MonsterHitBox->GetTransform()->SetLocalPosition(float4{0.f,250.f,static_cast<int>(ZOrder::Z01Actor02)});
	}

	{
		State_.CreateState("Intro", &Mr_Wheezy::Intro_Start, &Mr_Wheezy::Intro_Update, &Mr_Wheezy::Intro_End_);
		State_.CreateState("Idle", &Mr_Wheezy::Idle_Start, &Mr_Wheezy::Idle_Update, &Mr_Wheezy::Idle_End_);
		State_.CreateState("Attack", &Mr_Wheezy::Attack_Start, &Mr_Wheezy::Attack_Update, &Mr_Wheezy::Attack_End_);
		State_.CreateState("Defeat", &Mr_Wheezy::Defeat_Start, &Mr_Wheezy::Defeat_Update, &Mr_Wheezy::Defeat_End_);
		
		State_.CreateState("Chop", &Mr_Wheezy::Chop_Start, &Mr_Wheezy::Chop_Update, &Mr_Wheezy::Chop_End_);
		State_.CreateState("Clap", &Mr_Wheezy::Clap_Start, &Mr_Wheezy::Clap_Update, &Mr_Wheezy::Clap_End_);

		BattleState_.CreateState("BattleState_Battle",&Mr_Wheezy::BattleState_Battle_Start,&Mr_Wheezy::BattleState_Battle_Update,&Mr_Wheezy::BattleState_Battle_End);
		BattleState_.CreateState("BattleState_Dice",&Mr_Wheezy::BattleState_Dice_Start,&Mr_Wheezy::BattleState_Dice_Update,&Mr_Wheezy::BattleState_Dice_End);
	}

	BattleState_.ChangeState("BattleState_Dice");
	State_.ChangeState("Intro");

	//////////////½ºÅÝ
	Hp_ = 100;

}

void Mr_Wheezy::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);

	BattleState_.Update(_DeltaTime);
	State_.Update(_DeltaTime);
}

void Mr_Wheezy::SpawnCard()
{
	Dice_Card* _Dice_Card = GetLevel()->CreateActor<Dice_Card>();

	_Dice_Card->ImageRenderer->CreateAnimation("Card_Club.png", "Card_Club", 0, 20, 0.04f);
	_Dice_Card->ImageRenderer->SetChangeAnimation("Card_Club");

	_Dice_Card->Collision->SetCollisionGroup<CollisionGruop>(CollisionGruop::Monster);


	if (Hand_.Hand_Dir_ == Hand_Dir::Left)
	{
		_Dice_Card->GetTransform()->SetWorldPosition(float4{ 230.f, -460, static_cast<int>(ZOrder::Z01Actor04) });
		_Dice_Card->ImageRenderer->GetTransform()->SetLocalScaling(float4{ 230.f,240.f, 1.f });
		_Dice_Card->SetCardMove(float4{ 400.f,0.f });
	}
	else
	{
		_Dice_Card->GetTransform()->SetWorldPosition(float4{ 1050.f, -460, static_cast<int>(ZOrder::Z01Actor04) });
		_Dice_Card->ImageRenderer->GetTransform()->SetLocalScaling(float4{ -230.f,240.f, 1.f });
		_Dice_Card->SetCardMove(float4{ -400.f,0.f });
	}

	_Dice_Card->Collision->GetTransform()->SetLocalScaling(float4{ 80,210, 1.f });

	Cardvector_.push_back(_Dice_Card);
}

void Mr_Wheezy::SpawnParryCard()
{
	Dice_Card* _Dice_Card = GetLevel()->CreateActor<Dice_Card>();

	_Dice_Card->ImageRenderer->CreateAnimation("Card_Hraet.png", "Card_Hraet", 0, 20, 0.04f);
	_Dice_Card->ImageRenderer->SetChangeAnimation("Card_Hraet");

	_Dice_Card->Collision->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);

	if (Hand_.Hand_Dir_ == Hand_Dir::Left)
	{		
		_Dice_Card->GetTransform()->SetWorldPosition(float4{ 230.f, -460, static_cast<int>(ZOrder::Z01Actor04) });
		_Dice_Card->ImageRenderer->GetTransform()->SetLocalScaling(float4{ 230.f,240.f, 1.f });

		_Dice_Card->SetCardMove(float4{400.f,0.f});
	}
	else
	{		
		_Dice_Card->GetTransform()->SetWorldPosition(float4{ 1050.f, -460, static_cast<int>(ZOrder::Z01Actor04) });
		_Dice_Card->ImageRenderer->GetTransform()->SetLocalScaling(float4{ -230.f,240.f, 1.f });

		_Dice_Card->SetCardMove(float4{ -400.f,0.f });
	}

	_Dice_Card-> Collision->GetTransform()->SetLocalScaling(float4{ 150.f,230.f, 1.f });

	Cardvector_.push_back(_Dice_Card);
}

void Mr_Wheezy::CardClear()
{
	for (int i = 0; i < Cardvector_.size(); ++i)
	{
		Cardvector_[i]->Death();
	}

	Cardvector_.clear();
}