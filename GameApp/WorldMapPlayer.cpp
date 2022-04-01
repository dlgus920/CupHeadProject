#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCore.h>

#include "WorldMapPlayer.h"
#include "LoaddingScene.h"
#include "Image.h"

WorldMapPlayer::WorldMapPlayer() 
	: State_(this)
	, PlayerImageRenderer(nullptr)
	, PlayerCollision(nullptr)
	, KeyState_Update_(true)
	, ColState_Update_(true)
	, State_Update_(true)
	, KeyState_Up_(false)
	, KeyState_Down_(false)
	, KeyState_Left_(false)
	, KeyState_Right_(false)
	, KeyState_Chose_(false)
	, AniState_Chose_End_(false)
	, AniState_ScreenIris_End_(false)
	, ColState_{}
	, Dir_(AnimationDirection::Right)
	, MoveDir_{}
	, CurState_{}
{
}

WorldMapPlayer::~WorldMapPlayer() // default destructer 디폴트 소멸자
{

}

void WorldMapPlayer::Start()
{
	ComponentSetting();
	AnimationSetting();
	KeySetting();
	StateSetting();
}

void WorldMapPlayer::SetChangeAnimation(std::string _animation)
{
	PlayerImageRenderer->SetChangeAnimation(_animation);
}

void WorldMapPlayer::Move(float4 MoveDir, float _DeltaTime)
{
	GetTransform()->SetLocalMove(MoveDir * _DeltaTime);
}

void WorldMapPlayer::Move(float DirX, float DirY, float _DeltaTime)
{
	GetTransform()->SetLocalMove(float4(DirX, DirY, 0.f) * _DeltaTime);
}

std::string WorldMapPlayer::CheckState()
{
	if (true == KeyState_Chose_)
	{
		if (true == ColState_Chose_)
		{
			CurState_ = "Chose";
		}
	}

	else if (true == KeyState_Up_ ||
		true == KeyState_Down_ ||
		true == KeyState_Left_ ||
		true == KeyState_Right_ )
	{
		CurState_ = "Walk";
	}

	else
	{
		CurState_ = "Idle";
	}

	return CurState_;
}

StateInfo WorldMapPlayer::Idle_Start(StateInfo _state)
{
	//ChangeAnimation("Cup-Idle-Down");
	SetChangeAnimation("Cup-Idle-Down-Right");

	return StateInfo();
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
	// 실시간 업데이트가 너무 빨라 여기까지 오지를 못함,
	// MoveDir_이 float4::UPLEFT상태로 유지가 안됨 ㅋㅋㅋㅋ
	else if (MoveDir_ == float4::UPLEFT ||
		MoveDir_ == float4::UPRIGHT)
	{
		SetChangeAnimation("Cup-Idle-Up-Right");
	}

	else if (MoveDir_ == float4::DOWNLEFT ||
		MoveDir_ == float4::DOWNRIGHT)
	{
		SetChangeAnimation("Cup-Idle-Down-Right");
	}

	return StateInfo();
}

void WorldMapPlayer::Idle_End()
{
}

StateInfo WorldMapPlayer::Walk_Start(StateInfo _state)
{
	return StateInfo();
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

	else if (MoveDir_ == float4::UPLEFT ||
			MoveDir_ == float4::UPRIGHT)
	{
		SetChangeAnimation("Cup-Walk-Up-Right");
	}

	else if (MoveDir_ == float4::DOWNLEFT ||
			MoveDir_ == float4::DOWNRIGHT)
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

StateInfo WorldMapPlayer::Chose_Start(StateInfo _state)
{
	float4 pos = GetTransform()->GetWorldPosition();

	Image* IrisImage = GetLevel()->CreateActor<Image>();
	IrisImage->SetImageAnimationFolder("ScreenIris", "ScreenIris", 0.075f);
	IrisImage->GetImageRenderer()->SetAnimationReverse("ScreenIris");
	IrisImage->GetTransform()->SetLocalScaling(1280.f, 720.f);
	IrisImage->GetTransform()->SetWorldPosition(float4(pos.x, pos.y, static_cast<int>(ZOrder::Z00Fx00)));

	//IrisImage->SetImageAnimationEndFunc<WorldMapPlayer>("ScreenIris", &WorldMapPlayer::SetAniStateScreenIrisEnd, this);
	IrisImage->SetImageAnimationEndFunc<Image>("ScreenIris", &Image::Death, IrisImage);

	SetChangeAnimation("Cup-Chose");

	return StateInfo();
}

StateInfo WorldMapPlayer::Chose_Update(StateInfo _state, float _DeltaTime)
{
	if (true == AniState_Chose_End_)
	{
		/*if (true == AniState_ScreenIris_End_)
		{*/
			GameEngineCore::LevelFind<LoaddingScene>("LoaddingScene")->SetLoaddingNextLevel("Play");
			GameEngineCore::LevelChange("LoaddingScene");
		//}
	}

	//에니메이션 종료후, 페이드
	return StateInfo();
}

void WorldMapPlayer::Chose_End()
{
}

StateInfo WorldMapPlayer::LevelChangeWait_Start(StateInfo _state)
{


	return StateInfo();
}

StateInfo WorldMapPlayer::LevelChangeWait_Update(StateInfo _state, float _DeltaTime)
{
	if (true == AniState_ScreenIris_End_)
	{
		GameEngineCore::LevelFind<LoaddingScene>("LoaddingScene")->SetLoaddingNextLevel("Play");
		GameEngineCore::LevelChange("LoaddingScene");
	}
	return StateInfo();
}

void WorldMapPlayer::LevelChangeWait_End()
{
}

