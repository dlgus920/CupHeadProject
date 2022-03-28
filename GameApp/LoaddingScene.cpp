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

LoaddingScene::~LoaddingScene() // default destructer ����Ʈ �Ҹ���
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
	if (/* �ε� ��*/true == LoadEnd_ || GameEngineInput::GetInst().Down("Next")) //TODO : ������ ������ Start�� �Ϸ���� �˷������, �𷡽ð� ���ϸ��̼��� ������� �� ȥ�� ���� ġ�ٰ� Start�� �Ϸ�Ǹ� ������
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
