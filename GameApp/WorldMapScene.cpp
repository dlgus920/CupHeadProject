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

WorldMapScene::WorldMapScene() // default constructer ����Ʈ ������
{

}

WorldMapScene::~WorldMapScene() // default destructer ����Ʈ �Ҹ���
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
		_Map->GetCollisionMap()->SetAdjustImzgeSize();
	
		_Map->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z04CollisonMap00) });

		Image* MapImage = CreateActor<Image>();
		MapImage ->ImageSetImage("WorldMap_Background.png");
		MapImage ->SetAdjustImzgeSize();
		MapImage ->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z02Back10) });
	}

	{
		Object* WorldMapPoint = CreateActor<Object>();
		WorldMapPoint->GetImageRenderer()->SetImage("world_platforming_icon_0001.png");

		float4 size = WorldMapPoint->GetImageRenderer()->GetImageSize();

		WorldMapPoint->GetImageRenderer()->GetTransform()->SetLocalScaling(size);
		WorldMapPoint->GetObjectCollision()->GetTransform()->SetLocalScaling(size);

		WorldMapPoint->GetObjectCollision()->SetCollisionGroup(CollisionGruop::StagePoint);
		WorldMapPoint->GetObjectCollision()->SetCollisionType(CollisionType::Rect);
		WorldMapPoint->GetTransform()->SetWorldPosition(float4{ 500.f, -1000.f, static_cast<int>(ZOrder::Z01Actor02) });
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
	//������ ��
}

void WorldMapScene::LevelChangeStartEvent()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

}
