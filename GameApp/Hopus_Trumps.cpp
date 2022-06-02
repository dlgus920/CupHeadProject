#include "Precompile.h"
#include "Hopus_Trumps.h"
#include "Effect.h"
#include "Player.h"
#include "ParryObject.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineSoundManager.h>
#include <GameEngine/GameEngineSoundPlayer.h>


Hopus_Trumps::Hopus_Trumps()
	: BlendStart_(false)
	, Pos_Up_(false)
	, TimeCheck_(0.f)
	, FireImageRenderer_{nullptr}
	, FireCollision_{nullptr}
	, ParryCollision_{nullptr}
	, ParryNum_{0}
	, AttackStart_(false)
{
}

Hopus_Trumps::~Hopus_Trumps()
{
}

void Hopus_Trumps::Start()
{
	for (int i = 0; i < 9; ++i)
	{
		FireImageRenderer_[i] = CreateTransformComponent<GameEngineImageRenderer>();
		FireImageRenderer_[i]->CreateLevelAnimation("Rabit_Trumps.png", "Trumps_Clover", 0, 16, 0.04f, true);		
		FireImageRenderer_[i]->CreateLevelAnimation("Rabit_Trumps.png", "Trumps_Heart", 17, 33, 0.04f, true);		
		FireImageRenderer_[i]->CreateLevelAnimation("Rabit_Trumps.png", "Trumps_Dia", 34, 50, 0.04f, true);		
		FireImageRenderer_[i]->CreateLevelAnimation("Rabit_Trumps.png", "Trumps_Spade", 51, 67, 0.04f, true);
		FireImageRenderer_[i]->GetTransform()->SetLocalScaling(float4{ 90.f, 90.f,1.f });

		FireCollision_[i] = CreateTransformComponent<GameEngineCollision>();
		FireCollision_[i]->SetCollisionType(CollisionType::Rect);
		FireCollision_[i]->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
		FireCollision_[i]->GetTransform()->SetLocalScaling(float4{70.f, 70.f,1.f});

		FireImageRenderer_[i]->GetTransform()->SetLocalPosition(float4{ 90.f * i,0.f,0.f });
		FireCollision_[i]->GetTransform()->SetLocalPosition(float4{ 90.f * i,0.f,0.f });

		Trumpsorder_[i] = i;

		ParryCollision_[0] = CreateTransformComponent<GameEngineCollision>();
		ParryCollision_[0]->SetCollisionType(CollisionType::Rect);
		ParryCollision_[0]->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);
		ParryCollision_[0]->GetTransform()->SetLocalScaling(float4{ 90.f, 200.f,1.f });
		ParryCollision_[1] = CreateTransformComponent<GameEngineCollision>();
		ParryCollision_[1]->SetCollisionType(CollisionType::Rect);
		ParryCollision_[1]->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);
		ParryCollision_[1]->GetTransform()->SetLocalScaling(float4{ 90.f, 200.f,1.f });
	}

	Blendlate_ = { 1.f,1.f,1.f,0.f };

	for (int i = 0; i < 9; ++i)
	{
		FireImageRenderer_[i]->SetResultColor(Blendlate_);
	}

	Hopus_Trumps::Off();
}

void Hopus_Trumps::Update(float _DeltaTime)
{
	if (true == UserGame::StageInfo_.Debug_)
	{
		for (int i = 0; i < 9; ++i)
		{
			if (true == FireCollision_[i]->IsUpdate())
			{
				GetLevel()->PushDebugRender(FireCollision_[i]->GetTransform(), CollisionType::CirCle);
			}
		}

		if (true == ParryCollision_[0]->IsUpdate())
		{
			GetLevel()->PushDebugRender(ParryCollision_[0]->GetTransform(), CollisionType::CirCle, float4::PINK);
		}
		if (true == ParryCollision_[1]->IsUpdate())
		{
			GetLevel()->PushDebugRender(ParryCollision_[1]->GetTransform(), CollisionType::CirCle, float4::PINK);
		}
	}

	if (false == BlendStart_)
	{
		Blendlate_.a += _DeltaTime;

		if (Blendlate_.a > 1.f)
		{
			Blendlate_.a = 1.f;

			BlendStart_ = false;
		}

		for (int i = 0; i < 9; ++i)
		{
			FireImageRenderer_[i]->SetResultColor(Blendlate_);
		}
	}

	if (true == AttackStart_)
	{
		TimeCheck_ += _DeltaTime;

		if (true == Pos_Up_)
		{
			GetTransform()->SetWorldMove(float4{ 0.f,300.f,0.f }*_DeltaTime);
		}
		else
		{
			GetTransform()->SetWorldMove(float4{ 0.f,-300.f,0.f }*_DeltaTime);
		}

		if (TimeCheck_ > 3.f)
		{
			Off();
		}

		if (true == Parry_)
		{
			for (int i = 0; i < 9; ++i)
			{
				if (ParryCollision == FireCollision_[i])
				{
					FireImageRenderer_[i]->Off();
					FireCollision_[i]->Off();

					ParryCollision = nullptr;
					break;
				}
			}
		}
	}
}

void Hopus_Trumps::Parry(GameEngineCollision* ParriedCollision)
{
	Parry_ = true;

	ParryCollision = ParriedCollision;

	if (ParriedCollision == ParryCollision_[0])
	{
		FireImageRenderer_[ParryNum_[0]]->Off();
		FireCollision_[ParryNum_[0]]->Off();
		ParryCollision_[0]->Off();
	}
	else if (ParriedCollision == ParryCollision_[1])
	{
		FireImageRenderer_[ParryNum_[1]]->Off();
		FireCollision_[ParryNum_[1]]->Off();
		ParryCollision_[1]->Off();
	}
}

void Hopus_Trumps::Reset()
{
	{
		Hopus_Trumps::On();
		TimeCheck_ = 0.f;
		BlendStart_ = false;
		AttackStart_ = false;
		Blendlate_.a = 0.f;

		for (int i = 0; i < 9; ++i)
		{
			FireImageRenderer_[i]->On();
			FireCollision_[i]->On();
			FireImageRenderer_[i]->SetResultColor(Blendlate_);
		}

		ParryCollision_[0]->On();
		ParryCollision_[1]->On();
	}

	if (true == Pos_Up_)
	{
		GetTransform()->SetWorldPosition(float4{45.f,-45.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });
		Pos_Up_ = false;
	}
	else
	{
		GetTransform()->SetWorldPosition(float4{45.f,-700.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });
		Pos_Up_ = true;
	}

	{
		ParryNum_[0] = Rand_.RandomInt(0, 4);
		ParryNum_[1] = ParryNum_[0] + Rand_.RandomInt(3, 4);

		FireImageRenderer_[ParryNum_[0]]->SetChangeAnimation("Trumps_Heart");
		FireImageRenderer_[ParryNum_[1]]->SetChangeAnimation("Trumps_Heart");

		//FireCollision_[ParryNum_[0]]->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);
		//FireCollision_[ParryNum_[0]]->SetCollisionType(CollisionType::Rect);
		//FireCollision_[ParryNum_[0]]->GetTransform()->SetLocalScaling(float4{ 90.f, 200.f,1.f });

		//FireCollision_[ParryNum_[1]]->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);
		//FireCollision_[ParryNum_[1]]->SetCollisionType(CollisionType::Rect);
		//FireCollision_[ParryNum_[1]]->GetTransform()->SetLocalScaling(float4{ 90.f, 200.f,1.f });

		ParryCollision_[0]->GetTransform()->SetWorldPosition(FireCollision_[ParryNum_[0]]->GetTransform()->GetWorldPosition());;
		ParryCollision_[1]->GetTransform()->SetWorldPosition(FireCollision_[ParryNum_[1]]->GetTransform()->GetWorldPosition());;
		//FireCollision_[ParryNum_[0]]->Off();
		//FireCollision_[ParryNum_[1]]->Off();

		int aniorder = Rand_.RandomInt(0, 2);

		for (int i = 0; i < 9; ++i)
		{
			FireImageRenderer_[i]->GetTransform()->SetLocalPosition(float4{ 90.f * i,0.f,0.f });
			FireCollision_[i]->GetTransform()->SetLocalPosition(float4{ 90.f * i,0.f,0.f });


			FireCollision_[i]->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
			FireCollision_[i]->SetCollisionType(CollisionType::Rect);
			FireCollision_[i]->GetTransform()->SetLocalScaling(float4{ 70.f, 70.f,1.f });

			if (i == ParryNum_[0])
				continue;
			if (i == ParryNum_[1])
				continue;

			switch (aniorder)
			{
			case 0:
				FireImageRenderer_[i]->SetChangeAnimation("Trumps_Clover");
				break;
			case 1:
				FireImageRenderer_[i]->SetChangeAnimation("Trumps_Dia");
				break;
			case 2:
				FireImageRenderer_[i]->SetChangeAnimation("Trumps_Spade");
				break;
			}

			++aniorder;

			if (aniorder == 3)
			{
				aniorder = 0;
			}
		}
	}
}
