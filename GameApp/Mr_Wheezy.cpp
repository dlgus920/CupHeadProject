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
		MonsterImageRenderer->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-Intro",0,17,0.04f,false);
		MonsterImageRenderer->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-Idle",20,36,0.04f);
		MonsterImageRenderer->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-Attack",40,56,0.04f);

		MonsterImageRenderer->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-TellePort-In",60,93,0.04f,false);

		MonsterImageRenderer->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-TellePort-Out",93,60,0.04f,false);

		//MonsterImageRenderer->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-Ash_Pale",94,102,0.04f,false);

		MonsterImageRenderer->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-Death-Intro",103,107,0.04f);
		MonsterImageRenderer->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-Death-Idle",109,117,0.04f);

		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-Intro" ,std::bind(&Mr_Wheezy::AniEnd_Clap, this));

		MonsterImageRenderer->SetFrameCallBack("Mr_Wheezy-Attack", 49 ,std::bind(&Mr_Wheezy::AniEnd_Clap_Dice, this));

		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-TellePort-In" ,std::bind(&Mr_Wheezy::AniEnd_Clap, this));
		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-TellePort-Out" ,std::bind(&Mr_Wheezy::AniEnd_Clap, this));

		MonsterImageRenderer->SetEndCallBack("Mr_Wheezy-Death-Intro" ,std::bind(&Mr_Wheezy::AniEnd_Clap, this));


		MonsterImageRenderer->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
		//MonsterImageRenderer->GetTransform()->SetLocalPosition(float4(0.f, 0.f, static_cast<float>(ZOrder::Z01Actor03)));
		MonsterImageRenderer->SetChangeAnimation("Mr_Wheezy-Idle");


	}

	{
		MonsterHitBox = CreateTransformComponent<GameEngineCollision>();
		MonsterHitBox->SetCollisionType(CollisionType::Rect);
		MonsterHitBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterHitBox);
		MonsterHitBox->GetTransform()->SetLocalScaling(float4{ 350.f,625.f,1.f});
		MonsterHitBox->GetTransform()->SetLocalPosition(float4{ 0.f,-200.f,1.f});
	}

	
	//{
	//	State_.CreateState("Intro", &Mr_Wheezy::Intro_Start, &Mr_Wheezy::Intro_Update, &Mr_Wheezy::Intro_End_);
	//	State_.CreateState("Idle", &Mr_Wheezy::Idle_Start, &Mr_Wheezy::Idle_Update, &Mr_Wheezy::Idle_End_);
	//	State_.CreateState("Attack", &Mr_Wheezy::Attack_Start, &Mr_Wheezy::Attack_Update, &Mr_Wheezy::Attack_End_);
	//	State_.CreateState("Defeat", &Mr_Wheezy::Defeat_Start, &Mr_Wheezy::Defeat_Update, &Mr_Wheezy::Defeat_End_);
	//	
	//	State_.CreateState("Chop", &Mr_Wheezy::Chop_Start, &Mr_Wheezy::Chop_Update, &Mr_Wheezy::Chop_End_);
	//	State_.CreateState("Clap", &Mr_Wheezy::Clap_Start, &Mr_Wheezy::Clap_Update, &Mr_Wheezy::Clap_End_);

	//	BattleState_.CreateState("BattleState_Battle",&Mr_Wheezy::BattleState_Battle_Start,&Mr_Wheezy::BattleState_Battle_Update,&Mr_Wheezy::BattleState_Battle_End);
	//	BattleState_.CreateState("BattleState_Dice",&Mr_Wheezy::BattleState_Dice_Start,&Mr_Wheezy::BattleState_Dice_Update,&Mr_Wheezy::BattleState_Dice_End);
	//}

	//BattleState_.ChangeState("BattleState_Dice");
	//State_.ChangeState("Intro");

	//////////////½ºÅÝ
	Hp_ = 100;

}

void Mr_Wheezy::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MonsterHitBox->GetTransform(), CollisionType::Rect);
	//BattleState_.Update(_DeltaTime);
	//State_.Update(_DeltaTime);
}

void Mr_Wheezy::SpawnCard()
{
	//Dice_Card* _Dice_Card = GetLevel()->CreateActor<Dice_Card>();

	//_Dice_Card->ImageRenderer->CreateAnimation("Card_Club.png", "Card_Club", 0, 20, 0.04f);
	//_Dice_Card->ImageRenderer->SetChangeAnimation("Card_Club");

	//_Dice_Card->Collision->SetCollisionGroup<CollisionGruop>(CollisionGruop::Monster);


	//if (Hand_.Hand_Dir_ == Hand_Dir::Left)
	//{
	//	_Dice_Card->GetTransform()->SetWorldPosition(float4{ 230.f, -460, static_cast<int>(ZOrder::Z01Actor04) });
	//	_Dice_Card->ImageRenderer->GetTransform()->SetLocalScaling(float4{ 230.f,240.f, 1.f });
	//	_Dice_Card->SetCardMove(float4{ 400.f,0.f });
	//}
	//else
	//{
	//	_Dice_Card->GetTransform()->SetWorldPosition(float4{ 1050.f, -460, static_cast<int>(ZOrder::Z01Actor04) });
	//	_Dice_Card->ImageRenderer->GetTransform()->SetLocalScaling(float4{ -230.f,240.f, 1.f });
	//	_Dice_Card->SetCardMove(float4{ -400.f,0.f });
	//}

	//_Dice_Card->Collision->GetTransform()->SetLocalScaling(float4{ 80,210, 1.f });

	//Cardvector_.push_back(_Dice_Card);
}

void Mr_Wheezy::SpawnParryCard()
{
	//Dice_Card* _Dice_Card = GetLevel()->CreateActor<Dice_Card>();

	//_Dice_Card->ImageRenderer->CreateAnimation("Card_Hraet.png", "Card_Hraet", 0, 20, 0.04f);
	//_Dice_Card->ImageRenderer->SetChangeAnimation("Card_Hraet");

	//_Dice_Card->Collision->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);

	//if (Hand_.Hand_Dir_ == Hand_Dir::Left)
	//{		
	//	_Dice_Card->GetTransform()->SetWorldPosition(float4{ 230.f, -460, static_cast<int>(ZOrder::Z01Actor04) });
	//	_Dice_Card->ImageRenderer->GetTransform()->SetLocalScaling(float4{ 230.f,240.f, 1.f });

	//	_Dice_Card->SetCardMove(float4{400.f,0.f});
	//}
	//else
	//{		
	//	_Dice_Card->GetTransform()->SetWorldPosition(float4{ 1050.f, -460, static_cast<int>(ZOrder::Z01Actor04) });
	//	_Dice_Card->ImageRenderer->GetTransform()->SetLocalScaling(float4{ -230.f,240.f, 1.f });

	//	_Dice_Card->SetCardMove(float4{ -400.f,0.f });
	//}

	//_Dice_Card-> Collision->GetTransform()->SetLocalScaling(float4{ 150.f,230.f, 1.f });

	//Cardvector_.push_back(_Dice_Card);
}

void Mr_Wheezy::CardClear()
{
	//for (int i = 0; i < Cardvector_.size(); ++i)
	//{
	//	Cardvector_[i]->Death();
	//}

	//Cardvector_.clear();
}