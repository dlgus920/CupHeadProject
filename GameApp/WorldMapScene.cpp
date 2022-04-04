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
#include "Object.h"

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

		//_Map->MapImage_ = _Map->CreateTransformComponent<GameEngineImageRenderer>();
		////_Map->MapImage_->SetImage("WorldMap_PixelCheckBackground.png");
		//_Map->MapImage_->SetImage("WorldMap_Background.png");
		//_Map->MapImage_->SetAdjustImzgeSize();

		// 1280 720
		_Map->GetCollisionMap()->SetImage("WorldMap_PixelCheckBackground.png");
		_Map->GetTransform()->SetLocalScaling(float4{ 2424,1879,1.f });
		//_Map->GetCollisionMap()->SetAdjustImzgeSize();
	
		_Map->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z04CollisonMap00) });

		Image* MapImage = CreateActor<Image>();
		MapImage ->ImageSetImage("WorldMap_Background.png");
		MapImage ->SetAdjustImzgeSize();
		MapImage ->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z02Back10) });
	}

	{
		Object* WorldMapPoint = CreateActor<Object>();
		WorldMapPoint->GetImageRenderer()->SetImage("world_platforming_icon_0001.png");

		WorldMapPoint->GetImageRenderer()->GetTransform()->SetLocalScaling(float4{100.f,100.f,1.f});
		WorldMapPoint->GetObjectCollision()->GetTransform()->SetLocalScaling(float4{ 100.f,100.f,1.f });

		//WorldMapPoint->GetObjectCollision()->SetCollisionGroup(CollisionGruop::StagePoint);
		//WorldMapPoint->GetObjectCollision()->SetCollisionType(CollisionType::Rect);
		//WorldMapPoint->GetTransform()->SetWorldPosition(float4{ 500.f, -1000.f, static_cast<int>(ZOrder::Z01Actor02) });
	}

	{
		WorldMapPlayer_ = CreateActor<WorldMapPlayer>();
		WorldMapPlayer_->GetTransform()->SetWorldPosition(float4(500, -800.0f, static_cast<int>(ZOrder::Z01Actor01)));
		GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
	}

	//{
	//	TopUI* Actor = CreateActor<TopUI>();
	//	Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	//}
}

void WorldMapScene::LevelUpdate(float _DeltaTime)
{
	GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
}

void WorldMapScene::LevelChangeEndEvent()
{
	//릴리즈 맵
}

void WorldMapScene::LevelChangeStartEvent()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

}
