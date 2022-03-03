#include "PreCompile.h"
#include "TitleScene.h"

#include "Player.h"
#include "Monster.h"
#include "TopUI.h"
#include "Image.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/CameraActor.h>

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::LevelStart()
{
	//TODO: Level과 Level 사이의 메니저가 필요할것 같다.

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
	{
		Image* Actor = CreateActor<Image>();
		Actor->GetTransform()->SetWorldPosition(float4(200.0f, 0.0f, 0.0f));
		Actor->GetTransform()->SetWorldScaling(1.f,1.f);
		Actor->SetImage("title_screen_background.png");
	}

	{
		Image* Actor = CreateActor<Image>();
		Actor->GetTransform()->SetWorldPosition(float4(200.0f, 0.0f, 0.0f));
		Actor->GetTransform()->SetWorldScaling(1.f, 1.f);
		Actor->SetImage("title_screen_background.png");
	}
}

void TitleScene::LevelUpdate(float _DeltaTime)
{
}

void TitleScene::LevelChangeEndEvent()
{
	//Death();
}

void TitleScene::LevelChangeStartEvent()
{
}
