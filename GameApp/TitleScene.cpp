#include "PreCompile.h"
#include "TitleScene.h"
#include "LoaddingScene.h"

#include "Image.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCore.h>

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
	{
		Image* Actor = CreateActor<Image>();
		Actor->GetImageRenderer()->SetImage("title_screen_background.png");
		Actor->GetTransform()->SetWorldPosition(float4(200.0f, 0.0f, 0.0f));
		Actor->GetTransform()->SetWorldScaling(1.f,1.f);
		//Actor->GetImageRenderer()->CreateAnimationFolder();
		//Actor->GetImageRenderer()->CreateAnimation();
	}

	{
	//	Image* Actor = CreateActor<Image>();
	//	Actor->GetTransform()->SetWorldPosition(float4(200.0f, 0.0f, 0.0f));
	//	Actor->GetTransform()->SetWorldScaling(1.f, 1.f);
	//	Actor->SetImage("title_screen_background.png");
	}
}

void TitleScene::LevelUpdate(float _DeltaTime)
{
	if (false)
	{
		GameEngineCore::LevelCreate<LoaddingScene>("Loading")->SetNextLevel("WorldMap");;
		GameEngineCore::LevelChange("Loading");
	}
}

void TitleScene::LevelChangeEndEvent()
{
	//Death();
}

void TitleScene::LevelChangeStartEvent()
{
}

