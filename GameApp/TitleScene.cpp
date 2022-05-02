#include "PreCompile.h"
#include "TitleScene.h"
#include "LoaddingScene.h"

#include "UserGame.h"

#include "Image.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCore.h>

TitleScene::TitleScene()
	: TobeNext_(false)
	, FadeImage_(nullptr)
	, BlendRate_(0.f)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::LevelResourcesLoad()
{
	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("TitleScene");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());

			GameEngineTextureManager::GetInst().LoadLevelRes(this,AllFile[i].GetFullPath());
		}

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("TitleScreen"));

		GameEngineFolderTextureManager::GetInst().LoadLevelRes(this, TextureDir.PathToPlusFileName("TitleScreen"));
	}
}

void TitleScene::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	GameEngineInput::GetInst().CreateKey("Next", VK_SPACE);

	{
		Image* Actor = CreateActor<Image>();
		Actor->ImageRenderer_->SetImage("title_screen_background.png");
		Actor->ImageRenderer_->SetAdjustImzgeSize();
		Actor->GetTransform()->SetWorldPosition(float4(0.f, 0.0f, static_cast<int>(ZOrder::Z02Back03)));
	}

	{
		Image* Actor = CreateActor<Image>();
		Actor->ImageRenderer_->CreateAnimationFolder("TitleScreen", "TitleScreen", 0.04f, true);
		Actor->ImageRenderer_->SetChangeAnimation("TitleScreen");
		Actor->ImageRenderer_->SetAdjustImzgeSize();
		Actor->GetTransform()->SetWorldPosition(float4(0.f, -50.0f, static_cast<int>(ZOrder::Z02Back02)));
	}
	
	{
		Image* Image_ = CreateActor<Image>();
		Image_->ImageRenderer_->SetImage("Title_font.png");
		Image_->ImageRenderer_->SetAdjustImzgeSize();
		Image_->GetTransform()->SetWorldPosition(float4(0.f, -300.0f, static_cast<int>(ZOrder::Z02Back01)));
	}

	{
		FadeImage_ = CreateActor<Image>();
		FadeImage_->ImageRenderer_->SetImage("title_screen_background.png");
		FadeImage_->ImageRenderer_->SetAdjustImzgeSize();
		FadeImage_->GetTransform()->SetWorldPosition(float4(0.f, 0.f, static_cast<int>(ZOrder::Z00Fx00)));
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,0.f });
	}
}

void TitleScene::LevelUpdate(float _DeltaTime)
{

	//if (WM_ACTIVATE)
	//{
	//	int a = 0;
	//}

	if (false == TobeNext_)
	{
		if (GameEngineInput::GetInst().Down("Next"))
		{
			TobeNext_ = true;
		}
	}
	else
	{
		BlendRate_ += _DeltaTime*2;

		if (BlendRate_ >= 1.f)
		{
			LoaddingScene* LoaddingScene_ = dynamic_cast <LoaddingScene*>(GameEngineCore::LevelFind("LoaddingScene"));

			LoaddingScene_->SetLoaddingNextLevel(TitleScene::GetName(), "WorldMap");;
			LoaddingScene_->LevelResourcesLoad();
			LoaddingScene_->LevelStart();

			GameEngineCore::LevelChange("LoaddingScene");
		}
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
	}
}

void TitleScene::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	//Death();
}

void TitleScene::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -static_cast<int>(ZOrder::Z00Camera00)));
}

