#include "PreCompile.h"
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "LoaddingScene.h"
#include "WorldMapScene.h"
#include "Image.h"

LoaddingScene::LoaddingScene() 
	: NextScene_()
	, LoadEnd_(false)
	, CutIn_(false)
	, HourGlass_(nullptr)
{

}

LoaddingScene::~LoaddingScene() // default destructer 디폴트 소멸자
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
		Back->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f });

		BlendRate_ = 1.f;

		FadeImage_ = CreateActor<Image>();

		FadeImage_->ImageRenderer_->SetImage("title_screen_background.png");
		FadeImage_->GetTransform()->SetWorldPosition(float4{ 0.f, 0.f, static_cast<float>(ZOrder::Z00Fx00) });
		FadeImage_->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f });
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
	}
	

	GameEngineCore::LevelCreate<WorldMapScene>("WorldMap");
}

void LoaddingScene::LevelUpdate(float _DeltaTime)
{

	if (BlendRate_ >= 1.f)
	{
		CutIn_ = true;
	}

	if (true == CutIn_)
	{
		BlendRate_ -= _DeltaTime * 2;

		if (BlendRate_ < 0.f)
		{
			BlendRate_ = 0.f;

			CutIn_ = false;
		}
		FadeImage_->ImageRenderer_-> SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });

	}
	else
	{
		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 2.f)
		{
			BlendRate_ += _DeltaTime * 2;

			if (BlendRate_ >= 1.f || GameEngineInput::GetInst().Down("Next"))
			{
				GameEngineCore::LevelChange(NextScene_);

				NextScene_.clear();
				LoadEnd_ = false;
				HourGlass_->Death();
				HourGlass_ = nullptr;
			}
			FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
		}
	}
	
}

void LoaddingScene::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}

void LoaddingScene::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	GameEngineInput::GetInst().CreateKey("Next", VK_SPACE);

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -static_cast<int>(ZOrder::Z00Camera00)));

	HourGlass_ = CreateActor<Image>();
	HourGlass_->ImageCreateAnimation("HourGlass.png", "HourGlass", 0, 45, 0.05f, true);
	HourGlass_->ImageRenderer_->SetAdjustImzgeSize();
	HourGlass_->GetTransform()->SetWorldPosition(float4(450.f, -180.0f, static_cast<int>(ZOrder::Z01Actor02)));
	HourGlass_->ImageRenderer_->SetEndCallBack("HourGlass", std::bind(&LoaddingScene::LoadEnd, this));


}
