#include "Precompile.h"
#include "Hopus_Trumps.h"
#include "Effect.h"
#include "Player.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

Hopus_Trumps::Hopus_Trumps()
	: Roll_(false)
	, TimeCheck_(0.f)
	, Dist_(0.f)
	, FireImageRenderer_{nullptr}
	, FireCollision_{nullptr}
	, ParryCollision_{ nullptr }
	, ParryNum_(0)
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
		FireImageRenderer_[i]->CreateLevelAnimation("Rabit_Trumps.png", "Trumps_Clover", 0, 17, 0.04f, true);		
		FireImageRenderer_[i]->CreateLevelAnimation("Rabit_Trumps.png", "Trumps_Heart", 18, 35, 0.04f, true);		
		FireImageRenderer_[i]->CreateLevelAnimation("Rabit_Trumps.png", "Trumps_Dia", 36, 52, 0.04f, true);		
		FireImageRenderer_[i]->CreateLevelAnimation("Rabit_Trumps.png", "Trumps_Spade", 53, 69, 0.04f, true);
		FireImageRenderer_[i]->GetTransform()->SetLocalScaling(float4{ 90.f, 90.f,1.f });

		FireCollision_[i] = CreateTransformComponent<GameEngineCollision>();
		FireCollision_[i]->SetCollisionType(CollisionType::Rect);
		FireCollision_[i]->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
		FireCollision_[i]->GetTransform()->SetLocalScaling(float4{70.f, 70.f,1.f});

		FireImageRenderer_[i]->GetTransform()->SetLocalPosition(float4{ 90.f * i,0.f,0.f });
		FireCollision_[i]->GetTransform()->SetLocalPosition(float4{ 90.f * i,0.f,0.f });

		Trumpsorder_[i] = i;
	}

	ParryCollision_[0] = CreateTransformComponent<GameEngineCollision>();
	ParryCollision_[0]->SetCollisionType(CollisionType::Rect);
	ParryCollision_[0]->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);
	ParryCollision_[0]->GetTransform()->SetLocalScaling(float4{ 90.f, 100.f,1.f });

	ParryCollision_[1] = CreateTransformComponent<GameEngineCollision>();
	ParryCollision_[1]->SetCollisionType(CollisionType::Rect);
	ParryCollision_[1]->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);
	ParryCollision_[1]->GetTransform()->SetLocalScaling(float4{ 90.f, 100.f,1.f });

	Hopus_Trumps::Off();
}

void Hopus_Trumps::Update(float _DeltaTime)
{
	if (true == Roll_)
	{
		GetTransform()->SetWorldMove(float4{0.f,100.f,0.f}*_DeltaTime);

		if (TimeCheck_ >= 3.f)
		{
			GetTransform()->SetLocalRotationDegree(float4{ 0.f,0.f, 0.f }); // -> 회전 결과 3초뒤 다시 원위치로 돌아와야함

			Roll_ = false; 
		}
	}

	else
	{
		if (Dist_ <= 25.f)
		{
			Off(); 

			Effect* Boom = GetLevel()->CreateActor<Effect>();
			Boom->EffectAddAnimationActor("Rabit_Bomb.png", "Rabit_Bomb", float4{398.f,592.f,1.f}, 0, 15, 0.04f, false);
			Boom->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		}

		for (int i = 0; i < 8; ++i)
		{
		}
	}
}

void Hopus_Trumps::Reset(float4 _Pos)
{
	Hopus_Trumps::On();
	TimeCheck_ = 0.f;
	Roll_ = true;

	GetTransform()->SetWorldPosition(_Pos);

	int temp = 0;
	{
		//int rand = Rand_.RandomInt(0, 8);
		//int rand2 = Rand_.RandomInt(0, 8);


		//for (int i = 0; i < 50; ++i)
		//{
		//	temp = Trumpsorder_[rand];
		//	Trumpsorder_[rand] = Trumpsorder_[rand2];
		//	Trumpsorder_[rand2] = temp;
		//}
	}


	//TODO : ParryObject 시스템과 무관하다는것이 문제, 해결해야함
	// Parry 컬리젼을 만들지 말고 더미의 ParryObject를 만들고, 그새끼가 parry 한거 인식해서 렌더러 꺼주면 될듯


	{
		ParryNum_ = Rand_.RandomInt(0, 4);

		temp = ParryNum_ + Rand_.RandomInt(3, 4);

		FireImageRenderer_[ParryNum_]->SetChangeAnimation("Trumps_Heart");
		FireImageRenderer_[temp]->SetChangeAnimation("Trumps_Heart");

		ParryCollision_[ParryNum_]->GetTransform()->SetLocalPosition(FireImageRenderer_[ParryNum_]->GetTransform()->GetLocalPosition());
		ParryCollision_[temp]->GetTransform()->SetLocalPosition(FireImageRenderer_[temp]->GetTransform()->GetLocalPosition());

		int aniorder = Rand_.RandomInt(0, 2);

		for (int i = 0; i < 9; ++i)
		{
			if (i == ParryNum_)
				continue;
			if (i == temp)
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
