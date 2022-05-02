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

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}


void UserGame::Initialize()
{	
	// ShowCursor(false)
	// 
	//GameEngineInput::GetInst().HideCursor();

	//TransData.View.ViewToLH( { 0.0f, 0.0f, -10.0f }, {0.0f, 0.0f , 1.0f}, {0.0f, 1.0f , 0.0f});

	//TransData.Proj.OrthographicLH( 1280.f, 720.f, 0.1f, 1000.0f );


	//TransData.Scale.Scaling2D(200.0f);
	//TransData.Rotation.RotationDeg({ 0.0f, 0.0f, 45.0f });
	//TransData.Position.Translation({ 0.0f, 0.0f, 0.0f });
	//TransData.CalWorld();

	//GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	//Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);

	GameEngineCore::LevelCreate<TitleScene>("Title");
	GameEngineCore::LevelCreate<LoaddingScene>("LoaddingScene");
	GameEngineCore::LevelCreate<WorldMapScene>("WorldMap");
	GameEngineCore::LevelCreate<DicePaclace>("DicePaclace");
	GameEngineCore::LevelCreate<Stage_Mr_Wheezy>("Stage_Mr_Wheezy");

	GameEngineCore::LevelFind("Title")->LevelResourcesLoad();
	GameEngineCore::LevelFind("Title")->LevelStart();

	GameEngineCore::LevelChange("Title");

	return;
}

void UserGame::Release()
{

}

void UserGame::LoadingNextLevel(std::string _NextLevel)
{
	//LevelCreate<LoaddingScene>("Loading");
	//GameEngineLevel* FindLevel = LevelFind("Loading");
	//reinterpret_cast<LoaddingScene*>(FindLevel)->SetNextLevel(_NextLevel);
	//LevelChange("Loading");

	//LevelCreate<LoaddingScene>("Loading")->SetNextLevel(_NextLevel);
	//LevelChange("Loading");
}

//
//void UserGame::GameLoop()
//{
//	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
//	{
//		Pos.x += 0.001f;
//		TransData.Position.Translation(Pos);
//		TransData.CalWorld();
//
//
//		// ������ ������������ �ϳ��� ����
//		// �̾ȿ� ���������� �����ϰ���?
//		GameEngineDevice::RenderStart();
//
//		// �������Ӹ��� ��������� �ϴ°� ����?
//		// 
//		Pipe->Rendering();
//		GameEngineDevice::RenderEnd();
//	}
//}
//
//
