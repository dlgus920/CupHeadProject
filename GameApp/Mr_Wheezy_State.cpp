#include "PreCompile.h"
#include "Mr_Wheezy.h"
#include "Effect.h"

#include "Stage_Mr_Wheezy.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Mr_Wheezy::Intro_Start()
{
	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Intro");
}
void Mr_Wheezy::Intro_Update( float _DeltaTime)
{
	if (true == AniEnd_Intro_)
	{
		State_.ChangeState("Idle");
		return;
	}
}
void Mr_Wheezy::Intro_End_()
{
	AniEnd_Intro_ = false;
}

void Mr_Wheezy::Idle_Start()
{
	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Idle");
}
void Mr_Wheezy::Idle_Update(float _DeltaTime)
{
	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	//TimeCheck_ += _DeltaTime;

	//if (TimeCheck_ > 2.f)
	//{
	//	State_.ChangeState("Attack");
	//	return;
	//}
}
void Mr_Wheezy::Idle_End_()
{
	TimeCheck_ = 0.f;
}

void Mr_Wheezy::Attack_Start() // 외부에서 특정 조건 만족시 실행
{
	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Attack");
}
void Mr_Wheezy::Attack_Update( float _DeltaTime)
{
	if (Hp_ < 0)
	{
		State_.ChangeState("Defeat");
		return;
	}

	if (true == AniEnd_Attack_)
	{
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
void Mr_Wheezy::Attack_End_()
{
	AniEnd_Attack_ = false;
	AniEnd_Attack_End_ = false;

	TimeCheck_ = 0.f;
}

void Mr_Wheezy::Defeat_Start()
{
	TimeCheck_ = 0.f;
	MonsterHitBox->Off();

	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Death-Intro");

	Defeat_ = true;

	GetLevel<Stage_Mr_Wheezy>()->Knockout();
}
void Mr_Wheezy::Defeat_Update( float _DeltaTime)
{
	if (true == AniEnd_Death_Intro_)
	{
		Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-Death-Idle");
		AniEnd_Death_Intro_ = false;
	}

	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ >= 0.2f)
	{
		TimeCheck_ = 0.f;

		EffectDefeatRandom(250.f);
	} 
}
void Mr_Wheezy::Defeat_End_()
{
	AniEnd_Death_Intro_ = false;
	Defeat_ = false;
	TimeCheck_ = 0.f;
}

void Mr_Wheezy::Telleport_Start()
{
	Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-TellePort-In");
}
void Mr_Wheezy::Telleport_Update(float _DeltaTime)
{
	if (true == AniEnd_TellePort_In_)
	{
		ChangeCurRenderer();

		Cur_WheezyImageRenderer_->SetChangeAnimation("Mr_Wheezy-TellePort-Out");


		AniEnd_TellePort_In_ = false;
		//왼쪽에 있는지 오른쪽에 있는지 판별해서 옮겨주기
	}

	if (true == AniEnd_TellePort_HB_)
	{
		MoveHitBox();
		AniEnd_TellePort_HB_ = false;
	}

	if (true == AniEnd_TellePort_Out_)
	{
		ChangeAshImageRenderer();

		State_.ChangeState("Idle");
		AniEnd_TellePort_Out_ = false;
		return;
	}
}
void Mr_Wheezy::Telleport_End_()
{
	AniEnd_TellePort_In_ = false;
	AniEnd_TellePort_HB_ = false;
}
