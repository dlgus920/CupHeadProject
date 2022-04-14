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

void LoaddingScene::LevelResourcesLoad()
{
	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Loading");

		//GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("ScreenIris"));

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}
		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("HourGlass.png");
		Texture->Cut(16, 3);

	}
}

void LoaddingScene::LevelStart()
{	
	{
		Image* Back = CreateActor<Image>();
		Back->ImageSetImage("Loading_background.png");
		Back->GetTransform()->SetWorldPosition(float4(0.f, 0.0f, static_cast<int>(ZOrder::Z02Back01)));
		Back->SetAdjustImzgeSize();
	}
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
	GameEngineInput::GetInst().CreateKey("Next", VK_SPACE);

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -static_cast<int>(ZOrder::Z00Camera00)));

	HourGlass_ = CreateActor<Image>();
	HourGlass_->ImageCreateAnimation("HourGlass.png", "HourGlass", 0, 45, 0.05f, true);
	HourGlass_->SetAdjustImzgeSize();
	HourGlass_->GetTransform()->SetWorldPosition(float4(450.f, -180.0f, static_cast<int>(ZOrder::Z01Actor02)));
	HourGlass_->SetImageAnimationEndFunc<LoaddingScene>("HourGlass", &LoaddingScene::LoadEnd, this);


}
