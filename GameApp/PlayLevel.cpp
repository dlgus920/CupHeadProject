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
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		MouseActor* Actor = CreateActor<MouseActor>();
		Actor->GetUIRenderer()->SetRenderGroup(1000);  
	}

	{
		Map* Player = CreateActor<Map>();
		Player ->GetTransform()->SetWorldPosition(float4{ 1200.f, -1000.f, 100.0f });
		Player ->GetTransform()->SetWorldScaling(float4{ 2400, 2000.0f, 1.0f });
	}

	{
		Player* Actor = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Actor->GetTransform()->GetLocalPosition());
		Actor->GetTransform()->SetLocalPosition(float4(100.f, -100.0f, 1.0f));
	}

	{
		Monster* Actor = CreateActor<Monster>();
		Actor->GetTransform()->SetLocalPosition(float4(100.f, -100.0f, 2.0f));
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
