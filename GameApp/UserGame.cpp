#include "PreCompile.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

#include "TitleScene.h"

std::atomic<int> UserGame::LoadingFolder = 0;

UserGame::StageInfo UserGame::StageInfo_;

UserGame::UserGame() 
{
}

UserGame::~UserGame() 
{
}

UserGame::UserGame(UserGame&& _other) noexcept
{
}

void UserGame::Initialize()
{	
	GameEngineSoundManager::GetInst().CreateSoundChannel("Noise")->SetVolume(2.f);
	GameEngineSoundManager::GetInst().CreateSoundChannel("BGM");
	GameEngineSoundManager::GetInst().CreateSoundChannel("TitleBGM")->SetVolume(2.f);
	GameEngineSoundManager::GetInst().CreateSoundChannel("WorldBGM");
	GameEngineSoundManager::GetInst().CreateSoundChannel("Diceintro");
	GameEngineSoundManager::GetInst().CreateSoundChannel("Effect");
	GameEngineSoundManager::GetInst().CreateSoundChannel("DiceCardLoop");
	GameEngineSoundManager::GetInst().CreateSoundChannel("DiceChop")->SetVolume(2.f);
	GameEngineSoundManager::GetInst().CreateSoundChannel("Intro");
	GameEngineSoundManager::GetInst().CreateSoundChannel("Hopus_idle");// ->SetVolume(0.3f);
	GameEngineSoundManager::GetInst().CreateSoundChannel("Hopus_Attack");
	GameEngineSoundManager::GetInst().CreateSoundChannel("Hopus_Deffeat");
	GameEngineSoundManager::GetInst().SetGlobalVolume(0.25f);
	//GameEngineSoundManager::GetInst().CreateSoundChannel("BGM");


	StageInfo_.WorldMapPlayer_Pos_ = float4(500, -800.0f, static_cast<int>(ZOrder::Z01Actor00Player01));

	GameEngineCore::LevelCreate<TitleScene>("Title");
	GameEngineCore::LevelChange("Title");
}

void UserGame::Release()
{
}
