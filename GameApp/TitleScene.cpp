#include "PreCompile.h"
#include "TitleScene.h"
#include "WorldMapScene.h"



#include "Stage_Hopus_pocus.h"
#include "Stage_Mr_Wheezy.h"

#include "Image.h"
#include "UIBase.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineSoundPlayer.h>

TitleScene::TitleScene()
	: TobeNext_(false)
	, LoadState_(this)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::LevelStart()
{
	LoadState_.CreateState("ResourcesLoad", &TitleScene::ResourcesLoad_Start, &TitleScene::ResourcesLoad_Update, &TitleScene::ResourcesLoad_End);
	LoadState_.CreateState("LevelLoop", &TitleScene::LevelLoop_Start, &TitleScene::LevelLoop_Update, &TitleScene::LevelLoop_End);
	LoadState_.CreateState("Init", nullptr, &TitleScene::Init_Update, nullptr);

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	//CreateActor<UIBase>()->OldFilrmStart();
}

void TitleScene::Init_Update(float _DeltaTime)
{
	LoadState_.ChangeState("ResourcesLoad");
}

void TitleScene::ResourcesLoad_Start()
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
			//GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());

			GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
		}

		//GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("TitleScreen"));

		GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("TitleScreen"));
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			//GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());

			GameEngineSoundManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
		}
	}

	ResourcesLoadFadeInit();
}

void TitleScene::ResourcesLoad_Update(float _DeltaTime)
{
	if (0 >= UserGame::LoadingFolder)
	{
		LoadingComplete_ = true;
	}

	if (false == LoadingComplete_)
	{
		BlendRate_ -= _DeltaTime * 2.f;

		if (BlendRate_ < 0.f)
		{
			BlendRate_ = 0.f;
		}
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });

	}

	else
	{
		BlendRate_ += _DeltaTime * 2.f;

		if (BlendRate_ >= 1.f)
		{
			//LoadingFadeComplete_ = true;

			HourGlass_->Death();
			HourGlass_ = nullptr;
			LoadState_.ChangeState("LevelLoop");
		}

		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
	}
}

void TitleScene::ResourcesLoad_End()
{
}

void TitleScene::LevelLoop_Start()
{
	GameEngineSoundManager::GetInst().FindSoundChannel("Noise")->PlayLevelOverLap("sfx_OpticalLoop.wav",-1);
	

	SceneBGM_ = GameEngineSoundManager::GetInst().FindSoundChannel("TitleBGM");

	GameEngineInput::GetInst().CreateKey("Next", VK_SPACE);

	{
		Image* Actor = CreateActor<Image>();
		Actor->ImageRenderer_->SetLevelImage("title_screen_background.png");
		//Actor->ImageRenderer_->SetImage("title_screen_background.png");
		Actor->ImageRenderer_->SetAdjustImzgeSize();
		Actor->GetTransform()->SetWorldPosition(float4(0.f, 0.0f, static_cast<int>(ZOrder::Z02Back03)));
	}

	{
		Image* Actor = CreateActor<Image>();
		Actor->ImageRenderer_->CreateLevelAnimationFolder("TitleScreen", "TitleScreen", 0.04f, true);
		//Actor->ImageRenderer_->CreateAnimationFolder("TitleScreen", "TitleScreen", 0.04f, true);
		Actor->ImageRenderer_->SetChangeAnimation("TitleScreen");
		Actor->ImageRenderer_->SetAdjustImzgeSize();
		Actor->GetTransform()->SetWorldPosition(float4(0.f, -50.0f, static_cast<int>(ZOrder::Z02Back02)));
	}

	{
		Image* Image_ = CreateActor<Image>();
		Image_->ImageRenderer_->SetLevelImage("Title_font.png");
		//Image_->ImageRenderer_->SetImage("Title_font.png");
		Image_->ImageRenderer_->SetAdjustImzgeSize();
		Image_->GetTransform()->SetWorldPosition(float4(0.f, -300.0f, static_cast<int>(ZOrder::Z02Back01)));
	}

	{
		SceneBGM_->PlayLevelOverLap("bgm_title_screen.wav"); 
	}

	TimeCheck_ = 1.f;
}

void TitleScene::LevelLoop_Update(float _DeltaTime)
{
	static float soundTimeCheck_ = 0;
	static bool piano = false;

	soundTimeCheck_ += _DeltaTime;

	if (piano == false)
	{
		if (soundTimeCheck_ >= 40.f)
		{
			SceneBGM_->PlayLevelOverLap("bgm_title_screen_piano.wav");
			piano = true;
		}
	}
	if (false == TobeNext_)
	{
		LevelLoadFadeUpdate(_DeltaTime);

		if (GameEngineInput::GetInst().Down("Next"))
		{
			TobeNext_ = true;
		}
	}
	else
	{
		BlendRate_ += _DeltaTime * 2.f;
		TimeCheck_ -= _DeltaTime * 2.f;

		SceneBGM_->AdjustVolume(-_DeltaTime);

		if (BlendRate_ >= 1.f)
		{
			SceneBGM_->Stop();
			//GameEngineCore::LevelCreate<WorldMapScene>("WorldMap");
			//GameEngineCore::LevelChange("WorldMap");

			GameEngineCore::LevelCreate<Stage_Mr_Wheezy>("Stage_Mr_Wheezy");

			GameEngineCore::LevelChange("Stage_Mr_Wheezy");
		}
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
	}
}

void TitleScene::LevelLoop_End()
{
}

void TitleScene::LevelUpdate(float _DeltaTime)
{
	LoadState_.Update(_DeltaTime);
}

void TitleScene::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}

void TitleScene::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	LoadState_.ChangeState("Init");

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -static_cast<int>(ZOrder::Z00Camera00)));
}

