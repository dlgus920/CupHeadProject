#include "PreCompile.h"
#include "WorldMapPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void WorldMapPlayer::KeySetting()
{
	GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
	GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
	GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
	GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
	GameEngineInput::GetInst().CreateKey("Chose", VK_SPACE);
}

void WorldMapPlayer::StateSetting()
{
	
	State_.CreateState("Idle", &WorldMapPlayer::Idle_Start,
		&WorldMapPlayer::Idle_Update, &WorldMapPlayer::Idle_End);
	State_.CreateState("Walk", &WorldMapPlayer::Walk_Start,
		&WorldMapPlayer::Walk_Update, &WorldMapPlayer::Walk_End);
	State_.CreateState("Chose", &WorldMapPlayer::Chose_Start,
		&WorldMapPlayer::Chose_Update, &WorldMapPlayer::Chose_End);

}

void WorldMapPlayer::ComponentSetting()
{
	PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });

	PlayerCollision = CreateTransformComponent<GameEngineCollision>();
	PlayerCollision->CreateCollision<CollisionGruop>
		(CollisionType::Rect, CollisionGruop::Player, float4{ 100.0f, 100.0f, 1.0f });
}

void WorldMapPlayer::AnimationSetting()
{
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Up", 0, 15, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Up-Right", 16, 30, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Right",64 ,80 , 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Down", 112, 128, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Down-Right", 0, 7, 0.1f);

	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Up", 0, 15, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Up-Right", 16, 30, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Right", 64, 80, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Down", 112, 128, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Down-Right", 0, 7, 0.1f);

	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Chose", 0, 7, 0.1f);






}