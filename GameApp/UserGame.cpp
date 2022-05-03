#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

#include "TitleScene.h"
#include "LoaddingScene.h"

#include "WorldMapScene.h"

#include "DicePaclace.h"
#include "Stage_Mr_Wheezy.h"

std::atomic<int> UserGame::LoadingFolder = 0;

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
	GameEngineCore::LevelCreate<TitleScene>("Title");
	GameEngineCore::LevelCreate<WorldMapScene>("WorldMap");
	GameEngineCore::LevelCreate<DicePaclace>("DicePaclace");
	GameEngineCore::LevelCreate<Stage_Mr_Wheezy>("Stage_Mr_Wheezy");

	GameEngineCore::LevelChange("Title");

	return;
}

void UserGame::Release()
{
}
