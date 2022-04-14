#include "PreCompile.h"
#include "WorldMapPlayer.h"


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
	State_.CreateState("Entry", &WorldMapPlayer::Entry_Start,
		&WorldMapPlayer::Entry_Update, &WorldMapPlayer::Entry_End);

	State_.CreateState("Idle", &WorldMapPlayer::Idle_Start,
		&WorldMapPlayer::Idle_Update, &WorldMapPlayer::Idle_End);

	State_.CreateState("Walk", &WorldMapPlayer::Walk_Start,
		&WorldMapPlayer::Walk_Update, &WorldMapPlayer::Walk_End);

	State_.CreateState("Chose", &WorldMapPlayer::Chose_Start,
		&WorldMapPlayer::Chose_Update, &WorldMapPlayer::Chose_End);

	State_.CreateState("LevelChangeWait", &WorldMapPlayer::LevelChangeWait_Start,
		&WorldMapPlayer::LevelChangeWait_Update, &WorldMapPlayer::LevelChangeWait_End);

	State_.ChangeState("Entry");
}

void WorldMapPlayer::ComponentSetting()
{
	PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });

	PlayerCollision = CreateTransformComponent<GameEngineCollision>();
	PlayerCollision->SetCollisionType(CollisionType::Rect);
	PlayerCollision->SetCollisionGroup(static_cast<int>(CollisionGruop::Player));
	PlayerCollision->GetTransform()->SetLocalScaling({ 50.f, 50.f, 1.0f });

}

void WorldMapPlayer::AnimationSetting()
{
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Up", 4, 15, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Up-Right", 19, 30, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Right",51 ,61 , 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Down", 96, 108, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Walk-Down-Right", 68, 78, 0.1f);

	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Up", 0, 3, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Up-Right", 16, 18, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Right", 48, 50, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Down", 80, 86, 0.1f);
	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Idle-Down-Right", 64, 67, 0.1f);

	PlayerImageRenderer->CreateAnimation("WorldCuphead.png", "Cup-Chose", 112, 123, 0.1f, false);

	PlayerImageRenderer->SetEndCallBack("Cup-Chose",std::bind(& WorldMapPlayer::SetAniStateChoseEnd,this));

	PlayerImageRenderer->SetChangeAnimation("Cup-Idle-Down");
}
