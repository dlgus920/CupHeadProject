#include "PreCompile.h"
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "LoaddingScene.h"
#include "Image.h"

LoaddingScene::LoaddingScene() :
	NextScene_(),
	LoadEnd_(false)
{

}

LoaddingScene::~LoaddingScene() // default destructer 디폴트 소멸자
{

}

void LoaddingScene::LevelStart()
{	
	HourGlass_ = CreateActor<Image>();
	HourGlass_->SetImageAnimation("HourGlass", "HourGlass", 0, 45, 0.1f, true);
	HourGlass_->SetImageLocalScaling({200.f,320.f,0.f});
	//HourGlass_->GetImageRenderer()->
	//HourGlass_->get
}

void LoaddingScene::LevelUpdate(float _DeltaTime)
{
	if (/* 로딩 끝*/true == LoadEnd_) //TODO : 각각의 씬마다 Start가 완료됨을 알려줘야함, 모래시계 에니메이션은 쓰레드로 지 혼자 뺑이 치다가 Start가 완료되면 종료함
	{
		GameEngineCore::LevelChange(NextScene_);
	}
}

void LoaddingScene::LevelChangeEndEvent()
{
}

void LoaddingScene::LevelChangeStartEvent()
{
}
