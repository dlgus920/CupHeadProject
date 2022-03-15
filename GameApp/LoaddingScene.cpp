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
	HourGlass_ = CreateActor<Image>();
	HourGlass_->SetImageAnimation("HourGlass", "HourGlass", 0, 45, 0.1f, true);
	HourGlass_->SetImageLocalScaling({200.f,320.f,0.f});
	//HourGlass_->GetImageRenderer()->
	//HourGlass_->get
}

void LoaddingScene::LevelUpdate(float _DeltaTime)
{
	if (/* �ε� ��*/true == LoadEnd_) //TODO : ������ ������ Start�� �Ϸ���� �˷������, �𷡽ð� ���ϸ��̼��� ������� �� ȥ�� ���� ġ�ٰ� Start�� �Ϸ�Ǹ� ������
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
