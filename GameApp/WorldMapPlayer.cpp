#include "PreCompile.h"
#include "WorldMapPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

WorldMapPlayer::WorldMapPlayer() :
	State_(this),
	PlayerImageRenderer(nullptr),
	PlayerCollision(nullptr)
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

void WorldMapPlayer::Update(float _DeltaTime)
{
}

StateInfo WorldMapPlayer::Idle_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo WorldMapPlayer::Idle_Update(StateInfo _state, float _DeltaTime)
{
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
	return StateInfo();
}

void WorldMapPlayer::Walk_End()
{
}

StateInfo WorldMapPlayer::Chose_Start(StateInfo _state)
{
	return StateInfo();
}

StateInfo WorldMapPlayer::Chose_Update(StateInfo _state, float _DeltaTime)
{
	return StateInfo();
}

void WorldMapPlayer::Chose_End()
{
}

