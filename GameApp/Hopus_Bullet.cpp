#include "Precompile.h"
#include "Hopus_Bullet.h"
#include "Effect.h"
#include "Player.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineSoundManager.h>
#include <GameEngine/GameEngineSoundPlayer.h>

Hopus_Bullet::Hopus_Bullet() 
	: Roll_(false)
	, TimeCheck_(0.f)
	, Dist_(0.f)
	, FireImageRenderer{nullptr}
	, FireCollision{nullptr}
	, Dummy_(nullptr)
	, AttackStart_(false)
	, Fade_(false)
	, BlendRate_{ 1.f,1.f,1.f,0.f }
{
}

Hopus_Bullet::~Hopus_Bullet()
{
}

void Hopus_Bullet::Start()
{
	Dummy_ = GetLevel()->CreateActor<GameEngineActor>();
	
	for (int i = 0; i < 8; i++)
	{
		FireImageRenderer[i] = Dummy_->CreateTransformComponent<GameEngineImageRenderer>();

		FireImageRenderer[i]->CreateLevelAnimation("Rabit_Skull.png", "Rabit_Skull", 11, 21, 0.04f, true);
		
		FireImageRenderer[i]->SetChangeAnimation("Rabit_Skull");

		FireImageRenderer[i]->GetTransform()->SetLocalScaling(float4{ 114.f, 114.f,1.f });

		FireCollision[i] = CreateTransformComponent<GameEngineCollision>();
		FireCollision[i]->SetCollisionType(CollisionType::Rect);
		FireCollision[i]->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
		FireCollision[i]->GetTransform()->SetLocalScaling(float4{80.f, 80.f,1.f});

		i++;

		FireImageRenderer[i] = Dummy_->CreateTransformComponent<GameEngineImageRenderer>();

		FireImageRenderer[i]->CreateLevelAnimation("Rabit_Skull.png", "Rabit_Skull", 0, 10, 0.04f, true);

		FireImageRenderer[i]->SetChangeAnimation("Rabit_Skull");

		FireImageRenderer[i]->GetTransform()->SetLocalScaling(float4{ 114.f, 114.f,1.f });

		FireCollision[i] = CreateTransformComponent<GameEngineCollision>();
		FireCollision[i]->SetCollisionType(CollisionType::Rect);
		FireCollision[i]->SetCollisionGroup<CollisionGruop>(CollisionGruop::MonsterAttack);
		FireCollision[i]->GetTransform()->SetLocalScaling(float4{ 80.f, 80.f,1.f });

	}



	Dummy_->GameEngineActor::Off();
	Hopus_Bullet::Off();
}

void Hopus_Bullet::Update(float _DeltaTime)
{
	if (false == Fade_)
	{
		BlendRate_.a += _DeltaTime;
		if (BlendRate_.a >= 1.f)
		{
			BlendRate_.a = 1.f;
			Fade_ = true;
		}

		for (int i = 0; i < 8; i++)
		{
			FireImageRenderer[i]->SetResultColor(BlendRate_);
		}
	}

	if (true == UserGame::StageInfo_.Debug_)
	{
		for (int i = 0; i < 9; ++i)
		{
			if (true == FireCollision[i]->IsUpdate())
			{
				GetLevel()->PushDebugRender(FireCollision[i]->GetTransform(), CollisionType::CirCle);
			}
		}
	}

	if (true == Roll_)
	{
		float4 Pos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		Pos.y -= 75.f;

		GetTransform()->SetWorldPosition(Pos);
		TimeCheck_ += _DeltaTime;

		GetTransform()->SetLocalRotationDegree(float4{0.f,0.f,-TimeCheck_ *180.f}); // -> 회전 결과 3초뒤 다시 원위치로 돌아와야함

		for (int i = 0; i < 8; ++i)
		{
			FireImageRenderer[i]->GetTransform()->SetWorldPosition(FireCollision[i]->GetTransform()->GetWorldPosition());
		}

		if (true == AttackStart_)
		{
			GetTransform()->SetLocalRotationDegree(float4{ 0.f,0.f, 0.f }); // -> 회전 결과 3초뒤 다시 원위치로 돌아와야함

			Roll_ = false; 
		}
	}

	else
	{
		Dist_ -= _DeltaTime * 150.f;

		if (Dist_ <= 25.f)
		{
			Dummy_->Off();
			Off(); 

			GameEngineSoundManager::GetInst().FindSoundChannel("Effect")->PlayLevelOverLap("sfx_level_mouse_cannon_bomb_explode_01.wav");

			
			Effect* Boom = GetLevel()->CreateActor<Effect>();
			Boom->EffectAddAnimationActor("Rabit_Bomb.png", "Rabit_Bomb", float4{398.f,592.f,1.f}, 0, 15, 0.04f, false);
			Boom->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		}

		for (int i = 0; i < 8; ++i)
		{
			//FireImageRenderer[i]->GetTransform()->SetLocalPosition(float4{
			//	Dist_ * cosf(i * 45.f * GameEngineMath::DegreeToRadian),
			//	Dist_ * sinf(i * 45.f * GameEngineMath::DegreeToRadian) ,static_cast<float>(ZOrder::Z01Actor01Bullet01) });

			FireCollision[i]->GetTransform()->SetLocalPosition(float4{
				Dist_ * cosf(i * 45.f * GameEngineMath::DegreeToRadian),
				Dist_ * sinf(i * 45.f * GameEngineMath::DegreeToRadian) ,static_cast<float>(ZOrder::Z01Actor01Bullet01) });

			FireImageRenderer[i]->GetTransform()->SetWorldPosition(FireCollision[i]->GetTransform()->GetWorldPosition());
		}
	}
}

void Hopus_Bullet::Reset(float4 _PlayerPos)
{
	BlendRate_ = { 1.f,1.f,1.f,0.f };
	Fade_ = false;
	Dummy_->On();
	Hopus_Bullet::On();
	TimeCheck_ = 0.f;
	Roll_ = true;
	AttackStart_ = false;
	Dist_ = 250.f;

	GetTransform()->SetWorldPosition(_PlayerPos);
	Dummy_->GetTransform()->SetWorldPosition(_PlayerPos);

	for (int i = 0; i < 8; ++i)
	{
		FireImageRenderer[i]->SetResultColor(BlendRate_);
		FireImageRenderer[i]->On();
		FireCollision[i]->On();

		//FireImageRenderer[i]->GetTransform()->SetLocalPosition(float4{
		//	Dist_ * cosf(i * 45.f * GameEngineMath::DegreeToRadian),
		//	Dist_ * sinf(i * 45.f * GameEngineMath::DegreeToRadian) ,static_cast<float>(ZOrder::Z01Actor01Bullet01) });

		FireCollision[i]->GetTransform()->SetLocalPosition(float4{
			Dist_ * cosf(i * 45.f * GameEngineMath::DegreeToRadian),
			Dist_ * sinf(i * 45.f * GameEngineMath::DegreeToRadian) ,static_cast<float>(ZOrder::Z01Actor01Bullet01) }
		);

		FireImageRenderer[i]->GetTransform()->SetWorldPosition(FireCollision[i]->GetTransform()->GetWorldPosition());
	}

	int rand = Rand_.RandomInt(0, 3);
	//0,1,2,3
	rand *= 2;
	FireImageRenderer[rand]->Off();
	FireCollision[rand]->Off();

}
