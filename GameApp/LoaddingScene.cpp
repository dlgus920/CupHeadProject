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

	GameEngineInput::GetInst().CreateKey("Next", VK_SPACE);

	HourGlass_ = CreateActor<Image>();
	HourGlass_->SetImageAnimation("HourGlass.png", "HourGlass", 0, 45, 0.05f, true);
	HourGlass_->GetTransform()->SetWorldPosition(float4(0.f, 0.0f, static_cast<int>(ZOrder::Z01Actor01)));
	//HourGlass_->SetImageLocalScaling(float4{ 320.f,320.f,1.f });
	//HourGlass_->SetAdjustImzgeSize();

	HourGlass_->SetImageAnimationEndFunc<LoaddingScene>("HourGlass", &LoaddingScene::LoadEnd, this);
}

void LoaddingScene::LevelUpdate(float _DeltaTime)
{
	if (/* 로딩 끝*/true == LoadEnd_ || GameEngineInput::GetInst().Down("Next")) //TODO : 각각의 씬마다 Start가 완료됨을 알려줘야함, 모래시계 에니메이션은 쓰레드로 지 혼자 뺑이 치다가 Start가 완료되면 종료함
	{
		GameEngineCore::LevelChange(NextScene_);

		NextScene_.clear();
		LoadEnd_ = false;
		HourGlass_->Death();
		HourGlass_ = nullptr;
		//Death();
	}
}

void LoaddingScene::LevelChangeEndEvent()
{
}

void LoaddingScene::LevelChangeStartEvent()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -static_cast<int>(ZOrder::Z00Camera00)));

	HourGlass_->SetAnimationFrame(0);
	//HourGlass_->SetAdjustImzgeSize();

	
	//HourGlass_->GetImageRenderer()->
	//HourGlass_->get
}
