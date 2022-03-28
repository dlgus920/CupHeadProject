#include "PreCompile.h"
#include "WorldMapScene.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/MouseActor.h>

#include "Image.h"
#include "Map.h"



WorldMapScene::WorldMapScene() // default constructer 디폴트 생성자
{

}

WorldMapScene::~WorldMapScene() // default destructer 디폴트 소멸자
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
		Map* _Map = CreateActor<Map>();
		_Map->SetMapImage("WorldMap_Background.png", "WorldMap_PixelCheckBackground.png", 1212, -939.5);
	}

	{
		WorldMapPlayer_ = CreateActor<WorldMapPlayer>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
		WorldMapPlayer_->GetTransform()->SetLocalPosition(float4(100.f, -100.0f, static_cast<int>(ZOrder::Z01Actor01)));
	}

	{
		//Monster* Actor = CreateActor<Monster>();
		//Actor->GetTransform()->SetLocalPosition(float4(100.f, -100.0f, static_cast<int>(ZOrder::Actor02)));
		//float4 texsize = Actor->GetTextureSize();
		//float4 cutsize = Actor->GetCutSize();
		//float4 TextureScale = Actor->GetTextureScale();
	}

	//{
	//	TopUI* Actor = CreateActor<TopUI>();
	//	Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	//}
}

void WorldMapScene::LevelUpdate(float _DeltaTime)
{
}

void WorldMapScene::LevelChangeEndEvent()
{
	//릴리즈 맵
}

void WorldMapScene::LevelChangeStartEvent()
{
}
