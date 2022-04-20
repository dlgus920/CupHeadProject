#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"

#include "TopUI.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/MouseActor.h>

#include "Map.h"
#include "Image.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::LevelStart() 
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Camera00)));

	{
		//MouseActor* Actor = CreateActor<MouseActor>();
		//Actor->GetUIRenderer()->SetRenderGroup(1000);  
	}

	{
		
		Image* BackImage = CreateActor<Image>();
		BackImage->ImageSetImage("DicePalaceBack.png");
		BackImage->ImageRenderer_->SetAdjustImzgeSize();
		BackImage->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<int>(ZOrder::Z02Back10) });


		BackImage = CreateActor<Image>();
		BackImage->ImageSetImage("DicePalaceMain.png");
		BackImage->ImageRenderer_->SetAdjustImzgeSize();
		BackImage->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<int>(ZOrder::Z02Back09) });


		Map* _Map = CreateActor<Map>();

		//_Map->MapImage_ = _Map->CreateTransformComponent<GameEngineImageRenderer>();
		//_Map->MapImage_->SetImage("DicePalaceMain.png");
		//_Map->MapImage_->GetTransform()->SetLocalScaling(1280.f, 720.f);
		////_Map->MapImage_->SetAdjustImzgeSize();

		// 1280 720
		_Map->GetCollisionMap()->SetImage("DicePalaceCol.png");
		_Map->GetCollisionMap()->GetTransform()->SetLocalScaling(float4{ 1280.f, 720.f });

		_Map->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<int>(ZOrder::Z04CollisonMap01) });


		
		//_Map->SetMapImage("DicePalaceMain.png", "DicePalaceCol.png");
		// 
		//_Map->SetMapImage("WorldMap_Background.png", "WorldMap_PixelCheckBackground.png", 1212, -939.5);
		//_Map->GetTransform()->SetWorldPosition(float4{ 1200.f, -1000.f, static_cast<int>(ZOrder::Z04CollisonMap00) });
		//_Map->GetTransform()->SetWorldPosition(float4{ 0.f, 0.f, 100.0f });
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition(float4(900.f, -400.0f, static_cast<int>(ZOrder::Z01Actor02)));
	}

	{
		Monster* Actor = CreateActor<Monster>();
		Actor->GetTransform()->SetWorldPosition(float4(670.f, -120.f, static_cast<int>(ZOrder::Z01Actor03)));
		//float4 texsize = Actor->GetTextureSize();
		//float4 cutsize = Actor->GetCutSize();
		//float4 TextureScale = Actor->GetTextureScale();
	}

	//{
	//	TopUI* Actor = CreateActor<TopUI>();
	//	Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	//}

}

void PlayLevel::LevelUpdate(float _DeltaTime)
{
}
void PlayLevel::LevelChangeEndEvent()
{

}
void PlayLevel::LevelChangeStartEvent()
{

}
