#include "PreCompile.h"
#include "WorldMapPlayer.h"

#include <GameEngine/GameEngineCore.h>

#include "WorldMapScene.h"

void WorldMapPlayer::Idle_Start()
{
	//ChangeAnimation("Cup-Idle-Down");
	SetChangeAnimation("Cup-Idle-Down-Right");
}

StateInfo WorldMapPlayer::Idle_Update(StateInfo _state, float _DeltaTime)
{
	if (CheckState() != "Idle")
	{
		return CheckState();
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
	// �ǽð� ������Ʈ�� �ʹ� ���� ������� ������ ����,
	// MoveDir_�� float4::UPLEFT���·� ������ �ȵ� ��������
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

	return StateInfo();
}

void WorldMapPlayer::Idle_End()
{
}

void WorldMapPlayer::Walk_Start()
{
}

StateInfo WorldMapPlayer::Walk_Update(StateInfo _state, float _DeltaTime)
{
	if (CheckState() != "Walk")
	{
		return CheckState();
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
		return StateInfo();
	}
	if (ColState_.b_Down != 0 && MoveDir_.y < 0)
	{
		return StateInfo();
	}
	if (ColState_.b_Left != 0 && MoveDir_.x < 0)
	{
		return StateInfo();
	}
	if (ColState_.b_Right != 0 && MoveDir_.x > 0)
	{
		return StateInfo();
	}

	Move(MoveDir_ * 300.f, _DeltaTime);

	return StateInfo();
}

void WorldMapPlayer::Walk_End()
{
}

void WorldMapPlayer::Chose_Start()
{
	float4 pos = GetTransform()->GetWorldPosition();

	Image* IrisImage = GetLevel()->CreateActor<Image>();
	IrisImage->ImageCreateAnimationFolder("ScreenIris", "ScreenIris", 0.075f);
	IrisImage->GetImageRenderer()->SetAnimationReverse("ScreenIris");
	IrisImage->GetTransform()->SetLocalScaling(1280.f, 720.f);
	IrisImage->GetTransform()->SetWorldPosition(float4(pos.x, pos.y, static_cast<int>(ZOrder::Z00Fx00)));

	//IrisImage->SetImageAnimationEndFunc<WorldMapPlayer>("ScreenIris", &WorldMapPlayer::SetAniStateScreenIrisEnd, this);
	IrisImage->SetImageAnimationEndFunc<Image>("ScreenIris", &Image::Death, IrisImage);

	SetChangeAnimation("Cup-Chose");
}

StateInfo WorldMapPlayer::Chose_Update(StateInfo _state, float _DeltaTime)
{
	if (true == AniState_Chose_End_)
	{
		ChangeScene(ColState_Chose_->GetNextScene());
	}

	return StateInfo();
}

void WorldMapPlayer::Chose_End()
{
}

void WorldMapPlayer::LevelChangeWait_Start()
{
}

StateInfo WorldMapPlayer::LevelChangeWait_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}

void WorldMapPlayer::LevelChangeWait_End()
{
}