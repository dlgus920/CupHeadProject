#include "PreCompile.h"
#include "WorldMapScene.h"
#include "WorldMapPlayer.h"

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

		_Map->MapImage_ = _Map->CreateTransformComponent<GameEngineImageRenderer>();
		_Map->MapImage_->SetImage("WorldMap_Background.png");
		_Map->MapImage_->GetTransform()->SetLocalScaling(1212.f, 939.5f);
		//_Map->MapImage_->SetAdjustImzgeSize();

		// 1280 720
		_Map->CollisionMap_ = _Map->CreateTransformComponent<GameEngineImageRenderer>();
		_Map->CollisionMap_->SetImage("WorldMap_PixelCheckBackground.png");
		_Map->CollisionMap_->GetTransform()->SetLocalScaling(1212.f, 939.5f);
		//_Map->CollisionMap_->SetAdjustImzgeSize();

		float4 mapsize = _Map->MapImage_->GetCurrentTexture()->GetMetaDataImageSize();

		_Map->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<int>(ZOrder::Z04CollisonMap00) });
	}

	{
		WorldMapPlayer_ = CreateActor<WorldMapPlayer>();
		WorldMapPlayer_->GetTransform()->SetLocalPosition(float4(500, -800.0f, static_cast<int>(ZOrder::Z01Actor01)));
		GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
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
