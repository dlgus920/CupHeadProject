#include "Precompile.h"
#include "Hopus_Trumps.h"
#include "Effect.h"
#include "Player.h"
#include "ParryObject.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

Hopus_Trumps::Hopus_Trumps()
	: BlendStart_(false)
	, Pos_Up_(false)
	, TimeCheck_(0.f)
	, FireImageRenderer_{nullptr}
	, FireCollision_{nullptr}
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
	}

	ParryObject_[0] = GetLevel()->CreateActor<ParryObject>();
	ParryObject_[0]->ParryCollision = CreateTransformComponent<GameEngineCollision>();
	ParryObject_[0]->ParryObjectSetColOption(CollisionType::Rect, CollisionGruop::Parry);
	ParryObject_[0]->GetTransform()->SetLocalScaling(float4{ 90.f, 200.f,1.f });

	ParryObject_[1] = GetLevel()->CreateActor<ParryObject>();
	ParryObject_[1]->ParryCollision = CreateTransformComponent<GameEngineCollision>();
	ParryObject_[1]->ParryObjectSetColOption(CollisionType::Rect, CollisionGruop::Parry);
	ParryObject_[1]->GetTransform()->SetLocalScaling(float4{ 90.f, 200.f,1.f });

	Blendlate_ = { 1.f,1.f,1.f,0.f };

	ParryObject_[0]->Off();
	ParryObject_[1]->Off();

	Hopus_Trumps::Off();
}

void Hopus_Trumps::Update(float _DeltaTime)
{
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
			ParryObject_[0]->GetTransform()->SetWorldMove(float4{ 0.f,300.f,0.f }*_DeltaTime);
			ParryObject_[1]->GetTransform()->SetWorldMove(float4{ 0.f,300.f,0.f }*_DeltaTime);
		}
		else
		{
			GetTransform()->SetWorldMove(float4{ 0.f,-300.f,0.f }*_DeltaTime);			
			ParryObject_[0]->GetTransform()->SetWorldMove(float4{ 0.f,-300.f,0.f }*_DeltaTime);
			ParryObject_[1]->GetTransform()->SetWorldMove(float4{ 0.f,-300.f,0.f }*_DeltaTime);
		}

		if (TimeCheck_ > 3.f)
		{
			Off();
		}

		if (true == ParryObject_[0]->Parry_)
		{
			FireImageRenderer_[ParryNum_[0]]->Off();
			FireCollision_[ParryNum_[0]]->Off();
		}

		if (true == ParryObject_[1]->Parry_)
		{
			FireImageRenderer_[ParryNum_[1]]->Off();
			FireCollision_[ParryNum_[1]]->Off();
		}
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
		}

		ParryObject_[0]->On();
		ParryObject_[1]->On();

		ParryObject_[0]->Parry_ = false;
		ParryObject_[1]->Parry_ = false;
	}

	if (true == Pos_Up_)
	{
		GetTransform()->SetWorldPosition(float4{45.f,-45.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });
		Pos_Up_ = false;
	}
	else
	{
		GetTransform()->SetWorldPosition(float4{45.f,-675.f,static_cast<float>(ZOrder::Z01Actor01Bullet01) });
		Pos_Up_ = true;
	}

	{
		ParryNum_[0] = Rand_.RandomInt(0, 4);
		ParryNum_[1] = ParryNum_[0] + Rand_.RandomInt(3, 4);

		FireImageRenderer_[ParryNum_[0]]->SetChangeAnimation("Trumps_Heart");
		FireImageRenderer_[ParryNum_[1]]->SetChangeAnimation("Trumps_Heart");

		FireCollision_[ParryNum_[0]]->Off();
		FireCollision_[ParryNum_[1]]->Off();

		int aniorder = Rand_.RandomInt(0, 2);

		for (int i = 0; i < 9; ++i)
		{
			FireImageRenderer_[i]->GetTransform()->SetLocalPosition(float4{ 90.f * i,0.f,0.f });
			FireCollision_[i]->GetTransform()->SetLocalPosition(float4{ 90.f * i,0.f,0.f });

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

	ParryObject_[0]->GetTransform()->SetWorldPosition(FireImageRenderer_[ParryNum_[0]]->GetTransform()->GetWorldPosition());
	ParryObject_[1]->GetTransform()->SetWorldPosition(FireImageRenderer_[ParryNum_[1]]->GetTransform()->GetWorldPosition());
}
