#include "PreCompile.h"
#include "WorldMapPlayer.h"

#include <GameEngine/GameEngineCore.h>

#include "WorldMapScene.h"

void WorldMapPlayer::Entry_Start()
{
	SetChangeAnimation("Cup-Idle-Down");
}
void WorldMapPlayer::Entry_Update( float _DeltaTime)
{
	TimeCheck_ += _DeltaTime;
	if (TimeCheck_ > 1.f)
	{
		State_.ChangeState("Idle");
		return;
	}

	 
}
void WorldMapPlayer::Entry_End()
{
	TimeCheck_ = 0.f;
}

void WorldMapPlayer::Idle_Start()
{
	SetChangeAnimation("Cup-Idle-Down");
}
void WorldMapPlayer::Idle_Update( float _DeltaTime)
{
	if (CheckState() != "Idle")
	{
		State_.ChangeState(CheckState());
		return;
	}

	if (MoveDir_ == float4::UP)
	{
		SetChangeAnimation("Cup-Idle-Up");
	}

	else if (MoveDir_ == float4::DOWN)
	{
		SetChangeAnimation("Cup-Idle-Down");
	}

	else if (MoveDir_ == float4::LEFT ||
		MoveDir_ == float4::RIGHT)
	{
		SetChangeAnimation("Cup-Idle-Right");
	}
	// 실시간 업데이트가 너무 빨라 여기까지 오지를 못함,
	// MoveDir_이 float4::UPLEFT상태로 유지가 안됨 ㅋㅋㅋㅋ
	else if (MoveDir_ == float4::LEFTUP ||
		MoveDir_ == float4::RIGHTUP)
	{
		SetChangeAnimation("Cup-Idle-Up-Right");
	}

	else if (MoveDir_ == float4::LEFTDOWN ||
		MoveDir_ == float4::RIGHTDOWN)
	{
		SetChangeAnimation("Cup-Idle-Down-Right");
	}

	 
}
void WorldMapPlayer::Idle_End()
{
}

void WorldMapPlayer::Walk_Start()
{
	TimeCheck_ = 0.f;
}
void WorldMapPlayer::Walk_Update( float _DeltaTime)
{
	TimeCheck_ -= _DeltaTime;

	if (TimeCheck_ <= 0.f)
	{
		EffectDust();
		TimeCheck_ = 0.3f;
	}

	if (CheckState() != "Walk")
	{
		State_.ChangeState(CheckState());
		return;
	}

	if (MoveDir_ == float4::UP)
	{
		SetChangeAnimation("Cup-Walk-Up");
	}

	else if (MoveDir_ == float4::DOWN)
	{
		SetChangeAnimation("Cup-Walk-Down");
	}

	else if (MoveDir_ == float4::LEFT ||
		MoveDir_ == float4::RIGHT)
	{
		SetChangeAnimation("Cup-Walk-Right");
	}

	else if (MoveDir_ == float4::LEFTUP ||
		MoveDir_ == float4::RIGHTUP)
	{
		SetChangeAnimation("Cup-Walk-Up-Right");
	}

	else if (MoveDir_ == float4::LEFTDOWN ||
		MoveDir_ == float4::RIGHTDOWN)
	{
		SetChangeAnimation("Cup-Walk-Down-Right");
	}

	if (ColState_.b_Up != 0 && MoveDir_.y > 0)
	{
		MoveDir_.y = 0.f;
	}
	if (ColState_.b_Down != 0 && MoveDir_.y < 0)
	{
		MoveDir_.y = 0.f;
	}
	if (ColState_.b_Left != 0 && MoveDir_.x < 0)
	{
		MoveDir_.x = 0.f;
	}
	if (ColState_.b_Right != 0 && MoveDir_.x > 0)
	{
		MoveDir_.x = 0.f;
	}

	Move(MoveDir_ * 300.f, _DeltaTime);

	 
}
void WorldMapPlayer::Walk_End()
{
	TimeCheck_ = 0.f;
}

void WorldMapPlayer::Chose_Start()
{

	//float4 pos = GetTransform()->GetWorldPosition();

	//Image* IrisImage = GetLevel()->CreateActor<Image>();
	//IrisImage->ImageCreateAnimationFolder("ScreenIris", "ScreenIris", 0.055f);
	//IrisImage->GetImageRenderer()->SetAnimationReverse("ScreenIris");
	//IrisImage->GetTransform()->SetLocalScaling(float4{ 1280.f, 720.f });
	//IrisImage->GetTransform()->SetWorldPosition(float4(pos.x, pos.y, static_cast<int>(ZOrder::Z00Fx00)));
	//IrisImage->SetImageAnimationEndFunc<Image>("ScreenIris", &Image::Death, IrisImage);

	SetChangeAnimation("Cup-Chose");

	ChangeScene(ColState_Chose_->GetNextScene());
}
void WorldMapPlayer::Chose_Update( float _DeltaTime)
{
}
void WorldMapPlayer::Chose_End()
{
}