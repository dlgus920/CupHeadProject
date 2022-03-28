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

	GameEngineInput::GetInst().CreateKey("Next", VK_SPACE);

	{
		Image* Actor = CreateActor<Image>();
		Actor->SetImageTexture("title_screen_background.png");
		Actor->GetTransform()->SetWorldPosition(float4(0.f, 0.0f, static_cast<int>(ZOrder::Z02Back03)));
	}

	{
		Image* Actor = CreateActor<Image>();
		Actor->SetImageAnimationFolder("TitleScreen", "TitleScreen", 0.04f, true);
		Actor->GetTransform()->SetWorldPosition(float4(0.f, -50.0f, static_cast<int>(ZOrder::Z02Back02)));
	}
	
	{
		Image* Image_ = CreateActor<Image>();
		Image_->SetImageTexture("Title_font.png");
		Image_->GetTransform()->SetWorldPosition(float4(0.f, -300.0f, static_cast<int>(ZOrder::Z02Back01)));\
	}
}

void TitleScene::LevelUpdate(float _DeltaTime)
{
	if (GameEngineInput::GetInst().Down("Next"))
	{
		//GameEngineCore::LevelCreate<LoaddingScene>("Loading")->SetLoaddingNextLevel("WorldMap");;
		GameEngineCore::LevelCreate<LoaddingScene>("Loading")->SetLoaddingNextLevel("Play");;
		GameEngineCore::LevelChange("Loading");
		//TODO : 로딩씬 생성후 죽이기 or 초기화 작업
	}
}

void TitleScene::LevelChangeEndEvent()
{
	//Death();
}

void TitleScene::LevelChangeStartEvent()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -static_cast<int>(ZOrder::Z00Camera00)));
}

