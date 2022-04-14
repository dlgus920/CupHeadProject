#include "PreCompile.h"

#include "WorldMapPlayer.h"
#include "WorldMapScene.h"

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
	, ColState_Chose_(nullptr)
	, ColState_{}
	, Dir_(AnimationDirection::Right)
	, MoveDir_{}
	, CurState_{}
	, TimeCheck_(0.f)
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

void WorldMapPlayer::ChangeScene(std::string _Scene)
{
	GetLevel<WorldMapScene>()->ChangeScene(_Scene);
}

void WorldMapPlayer::Entry()
{
	State_.ChangeState("Entry");
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
		if (nullptr != ColState_Chose_)
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





