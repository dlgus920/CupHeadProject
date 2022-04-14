#include "PreCompile.h"
#include "WorldMapScene.h"

#include "LoaddingScene.h"
#include "DicePaclace.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/MouseActor.h>

#include "Image.h"
#include "Map.h"
#include "Object.h"
#include "StagePoint.h"
#include "WorldMapPlayer.h"


WorldMapScene::WorldMapScene() // default constructer ����Ʈ ������
{

}

WorldMapScene::~WorldMapScene() // default destructer ����Ʈ �Ҹ���
{

}

void WorldMapScene::LevelResourcesLoad()
{
}

void WorldMapScene::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

	{
		//MouseActor* Actor = CreateActor<MouseActor>();
		//Actor->GetUIRenderer()->SetRenderGroup(1000);  
	}

	{
		// 1280 720
		Map* _Map = CreateActor<Map>();
		_Map->GetCollisionMap()->SetImage("WorldMap_PixelCheckBackground.png");
		_Map->GetCollisionMap()->SetAdjustImzgeSize();
		_Map->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z04CollisonMap00) });

		Image* MapImage = CreateActor<Image>();
		MapImage ->ImageSetImage("WorldMap_Background.png");
		MapImage ->SetAdjustImzgeSize();
		MapImage ->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z02Back10) });
	}

	{
		StagePoint* WorldMapPoint = CreateActor<StagePoint>();
		WorldMapPoint->GetTransform()->SetWorldPosition(float4{ 500.f, -1000.f, static_cast<int>(ZOrder::Z01Actor02) });

		WorldMapPoint->SetNextScene("DicePaclace");
	}

	{
		WorldMapPlayer_ = CreateActor<WorldMapPlayer>();
		WorldMapPlayer_->GetTransform()->SetWorldPosition(float4(500, -800.0f, static_cast<int>(ZOrder::Z01Actor00Player01)));
		GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
	}

	//{
	//	TopUI* Actor = CreateActor<TopUI>();
	//	Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	//}
	{
		GameEngineCore::LevelCreate<DicePaclace>("DicePaclace");

	}
}

void WorldMapScene::LevelUpdate(float _DeltaTime)
{
	GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
}

void WorldMapScene::LevelChangeEndEvent()
{
	//������ ��
}

void WorldMapScene::LevelChangeStartEvent()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

}

void WorldMapScene::ChangeScene(std::string _Scene)
{
#ifdef _DEBUG
	if (nullptr == GameEngineCore::LevelFind(_Scene))
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ����");
	}
#endif // _DEBUG

	dynamic_cast <LoaddingScene*>(GameEngineCore::LevelFind("LoaddingScene"))
		->SetLoaddingNextLevel(_Scene);

	GameEngineCore::LevelChange("LoaddingScene");

}
