#include "PreCompile.h"
#include "Hopus_pocus.h"
#include "Effect.h"

#include "Stage_Hopus_pocus.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Hopus_pocus::Intro_Start()
{
	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_pocus-Intro");
}
void Hopus_pocus::Intro_Update( float _DeltaTime)
{
	if (true == AniEnd_Intro_)
	{
		State_.ChangeState("Idle");
		return;
	}
}
void Hopus_pocus::Intro_End_()
{
	AniEnd_Intro_ = false;
}

void Hopus_pocus::Idle_Start()
{
	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_pocus-Idle");
}
void Hopus_pocus::Idle_Update(float _DeltaTime)
{
	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ > 2.5f)
	{
		if (FireCount_ == 3)
		{
			FireCount_ = 0;
			State_.ChangeState("Telleport");
			return;
		}

		State_.ChangeState("Attack");
		return;
	}
}
void Hopus_pocus::Idle_End_()
{
	TimeCheck_ = 0.f;
}

void Hopus_pocus::Attack_Start() // 외부에서 특정 조건 만족시 실행
{
	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_pocus-Attack");
}
void Hopus_pocus::Attack_Update( float _DeltaTime)
{
	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	if (true == AniEnd_Attack_)
	{
		Firefire();
		FireCount_++;

		AniEnd_Attack_ = false;
	}

	if (true == AniEnd_Attack_End_)
	{
		State_.ChangeState("Idle");
		return;
	}	

#ifdef _DEBUG
	else
	{
	}
#endif // !_DEBUG
	 
}
void Hopus_pocus::Attack_End_()
{
	AniEnd_Attack_ = false;
	AniEnd_Attack_End_ = false;

	TimeCheck_ = 0.f;
}

void Hopus_pocus::Defeat_Start()
{
	TimeCheck_ = 0.f;
	MonsterHitBox->Off();
	MonsterBox->Off();

	Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_pocus-Death-Intro");

	Defeat_ = true;

	GetLevel<Stage_Hopus_pocus>()->Knockout();
}
void Hopus_pocus::Defeat_Update(float _DeltaTime)
{
	if (true == AniEnd_Death_Intro_)
	{
		Hopus_pocusImageRenderer_->SetChangeAnimation("Hopus_pocus-Death-Idle");
		AniEnd_Death_Intro_ = false;
	}

	TimeCheck_ += _DeltaTime;

	static bool updown = true;

	if (TimeCheck_ >= 0.2f)
	{
		TimeCheck_ = 0.f;

		float4 pos = Hopus_pocusImageRenderer_->GetTransform()->GetWorldPosition();
		pos.y - 250.f;

		EffectDefeatRandom(250.f, pos);

		if (updown)
			updown = false;
		else
			updown = true;
	} 

	if (updown)
	{
		Hopus_pocusImageRenderer_->GetTransform()->SetWorldMove(float4{ 0.f,400.f * _DeltaTime });
	}
	else
	{
		Hopus_pocusImageRenderer_->GetTransform()->SetWorldMove(float4{ 0.f,-400.f * _DeltaTime });
	}
}
void Hopus_pocus::Defeat_End_()
{
	AniEnd_Death_Intro_ = false;
	Defeat_ = false;
	TimeCheck_ = 0.f;
}
