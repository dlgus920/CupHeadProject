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

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::LevelStart() 
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

	{
		//MouseActor* Actor = CreateActor<MouseActor>();
		//Actor->GetUIRenderer()->SetRenderGroup(1000);  
	}

	{
		Map* _Map = CreateActor<Map>();
		//_Map->SetMapImage("WorldMap_Background.png", "WorldMap_PixelCheckBackground.png", 1212, -939.5);
		_Map->SetMapImage("Map.png", "Map.png", 1200.f, -1000.f);
		//_Map->GetTransform()->SetWorldPosition(float4{ 1200.f, -1000.f, static_cast<int>(ZOrder::Z04CollisonMap00) });
		//_Map->GetTransform()->SetWorldPosition(float4{ 0.f, 0.f, 100.0f });
	}

	{
		Player* Actor = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Actor->GetTransform()->GetLocalPosition());
		Actor->GetTransform()->SetLocalPosition(float4(100.f, -100.0f, static_cast<int>(ZOrder::Z01Actor01)));
	}

	{
		Monster* Actor = CreateActor<Monster>();
		Actor->GetTransform()->SetLocalPosition(float4(100.f, -100.0f, static_cast<int>(ZOrder::Z01Actor02)));
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
