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
	//TODO: 일단 첫 로딩을 거친다. 가장 기본적인 리소스를 불러오고, 메인 타이틀 씬을 재생한다. 재생중 동작을 인식하여
	//		더 진행할지, 종료할지 결정후, 더 진행할 경우, 로딩씬을 재생하며 다음씬에 필요한 리소스들을 로딩한다.
	//		첫 로딩과 둘째 로딩은 서로 다르게 진행할 것이다.
	//		첫 로딩은 기본적인 쉐이더, 디렉토리 리소스 등등을 불러온다.
	//		둘째 로딩은 해당씬에 필요한 정보들을 셋팅하는 단계가 될것이다.
	//		결국 가장 먼저 첫 로딩씬에 필요한 리소스들을 가장 먼저 불러오고, 불러온뒤 동작을 인식하여 다른것들을 불러오게 한다.

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

