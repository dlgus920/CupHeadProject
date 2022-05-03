#include "Precompile.h"
#include "Stage_Mr_Wheezy.h"

#include "LoaddingScene.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/MouseActor.h>
#include <GameEngine/GameEngineCore.h>

#include "UserGame.h"

#include "Map.h"
#include "Image.h"
#include "Effect.h"
#include "Player.h"
#include "Mr_Wheezy.h"

Stage_Mr_Wheezy::Stage_Mr_Wheezy()
	: PhaseState_(this)
	, LoadState_(this)
	, Mr_Wheezy_(nullptr)
	, BackImageRenderer_{nullptr}
{
}

Stage_Mr_Wheezy::~Stage_Mr_Wheezy()
{
}

void Stage_Mr_Wheezy::LevelStart()
{
	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -static_cast<int>(ZOrder::Z00Camera00)));

	PhaseState_.CreateState("Intro", &Stage_Mr_Wheezy::Intro_Start, &Stage_Mr_Wheezy::Intro_Update, &Stage_Mr_Wheezy::Intro_End);
	PhaseState_.CreateState("Playing", &Stage_Mr_Wheezy::Playing_Start, &Stage_Mr_Wheezy::Playing_Update, &Stage_Mr_Wheezy::Playing_End);

	LoadState_.CreateState("ResourcesLoad", &Stage_Mr_Wheezy::ResourcesLoad_Start, &Stage_Mr_Wheezy::ResourcesLoad_Update, &Stage_Mr_Wheezy::ResourcesLoad_End);
	LoadState_.CreateState("LevelLoop", &Stage_Mr_Wheezy::LevelLoop_Start, &Stage_Mr_Wheezy::LevelLoop_Update, &Stage_Mr_Wheezy::LevelLoop_End);
	LoadState_.CreateState("Init", nullptr, &Stage_Mr_Wheezy::Init_Update, nullptr);
}

void Stage_Mr_Wheezy::Init_Update(float _DeltaTime) 
{
	LoadState_.ChangeState("ResourcesLoad");
}
void Stage_Mr_Wheezy::ResourcesLoad_Start()
{
	PlayerResourceLoad();
	SceneResourceLoad();

	UserGame::LoadingFolder++;
	GameEngineCore::ThreadQueue.JobPost
	(
		[]()
		{
			GameEngineDirectory TextureDir;
			TextureDir.MoveParent(GV_GAMEFILENAME);
			TextureDir.MoveChild("Resources");
			TextureDir.MoveChild("Image");
			TextureDir.MoveChild("DicePalace");
			TextureDir.MoveChild("MiniBoss");
			TextureDir.MoveChild("Mr_Wheezy");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
					//LevelTextureLoad(AllFile[i].GetFullPath());
				}
			}

			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Intro_Flame.png");
			Texture->Cut(10, 1);
			Texture = GameEngineTextureManager::GetInst().Find("Intro_Hand.png");
			Texture->Cut(14, 1);
			Texture = GameEngineTextureManager::GetInst().Find("Mr_Wheezy.png");
			Texture->Cut(20, 6);
			Texture = GameEngineTextureManager::GetInst().Find("Smoke_FX.png");
			Texture->Cut(20, 3);
			//GameEngineTexture* Texture = LevelTextureFind("Intro_Flame.png");
			//Texture->Cut(10, 1);
			//Texture = LevelTextureFind("Intro_Hand.png");
			//Texture->Cut(14, 1);
			//Texture = LevelTextureFind("Mr_Wheezy.png");
			//Texture->Cut(20, 6);
			//Texture = LevelTextureFind("Smoke_FX.png");
			//Texture->Cut(20, 3);

			UserGame::LoadingFolder--;
		}
	);

	UserGame::LoadingFolder++;
	GameEngineCore::ThreadQueue.JobPost
	(
		[]()
		{
			GameEngineDirectory TextureDir;
			TextureDir.MoveParent(GV_GAMEFILENAME);
			TextureDir.MoveChild("Resources");
			TextureDir.MoveChild("Image");
			TextureDir.MoveChild("DicePalace");
			TextureDir.MoveChild("MiniBoss");
			TextureDir.MoveChild("Mr_Wheezy");
			TextureDir.MoveChild("BackGround");

			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("BG_top_smoke"));

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
					//LevelTextureLoad(AllFile[i].GetFullPath());
				}
			}

			TextureDir.MoveChild("BG_Fire");
			//LevelFolderTextureLoad(TextureDir.PathToPlusFileName("BG_Fire_Back"));
			//LevelFolderTextureLoad(TextureDir.PathToPlusFileName("BG_Fire_Front"));
			//LevelFolderTextureLoad(TextureDir.PathToPlusFileName("BG_Fire_Middle"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("BG_Fire_Back"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("BG_Fire_Front"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("BG_Fire_Middle"));
			UserGame::LoadingFolder--;
		}
	);

	ResourcesLoadFadeInit();
}

void Stage_Mr_Wheezy::ResourcesLoad_Update(float _DeltaTime)
{
	if (0 >= UserGame::LoadingFolder)
	{
		LoadingComplete_ = true;
	}

	if (false == LoadingComplete_)
	{
		BlendRate_ -= _DeltaTime * 2;

		if (BlendRate_ < 0.f)
		{
			BlendRate_ = 0.f;
		}
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });

	}

	else
	{
		BlendRate_ += _DeltaTime * 2;

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
void Stage_Mr_Wheezy::ResourcesLoad_End()
{
}
void Stage_Mr_Wheezy::LevelLoop_Start()
{
	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	FadeImage_->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00)));

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Camera00)));

	{
		GameEngineActor* BackImage = CreateActor<GameEngineActor>();
		GameEngineImageRenderer* BackRenderer;

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1320.f,732.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-360.f,static_cast<float>(ZOrder::Z02Back01) });
		BackRenderer->CreateAnimationFolder("BG_top_smoke", "BG_top_smoke", 0.04f);
		BackRenderer->SetChangeAnimation("BG_top_smoke");
		BackRenderer->SetResultColor(float4{ 1.f, 1.f, 1.f, 0.5f });

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 312.f,277.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 1180,-600,static_cast<float>(ZOrder::Z02Back01) });
		BackRenderer->SetImage("kd_cigar_bg_smoke_fg.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1500.f,750.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-450.f,static_cast<float>(ZOrder::Z02Back02) });
		BackRenderer->CreateAnimationFolder("BG_Fire_Front", "BG_Fire_Front", 0.04f);
		BackRenderer->SetChangeAnimation("BG_Fire_Front");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,360.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 240.f,-550.f,static_cast<float>(ZOrder::Z02Back03) });
		BackRenderer->SetImage("Ashtray_left_fr.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,360.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 240.f,-550.f,static_cast<float>(ZOrder::Z02Back06) });
		BackRenderer->SetImage("Ashtray_left_bk.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,360.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 1040.f,-550.f,static_cast<float>(ZOrder::Z02Back03) });
		BackRenderer->SetImage("Ashtray_right_fr.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,360.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 1040.f,-550.f,static_cast<float>(ZOrder::Z02Back06) });
		BackRenderer->SetImage("Ashtray_right_bk.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1500.f,750.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-375.f,static_cast<float>(ZOrder::Z02Back07) });
		BackRenderer->CreateAnimationFolder("BG_Fire_Middle", "BG_Fire_Middle", 0.04f);
		BackRenderer->SetChangeAnimation("BG_Fire_Middle");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1500.f,750.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-300.f,static_cast<float>(ZOrder::Z02Back08) });
		BackRenderer->CreateAnimationFolder("BG_Fire_Back", "BG_Fire_Back", 0.04f);
		BackRenderer->SetChangeAnimation("BG_Fire_Back");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1379.f,720.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-360.f,static_cast<float>(ZOrder::Z02Back09) });
		BackRenderer->SetImage("Mr_Wheezy_Back.png");

		BackImageRenderer_[0] = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackImageRenderer_[0]->GetTransform()->SetLocalScaling(float4{ 2048.f,556.f });
		BackImageRenderer_[0]->GetTransform()->SetWorldPosition(float4{ 0.f,-278.f,static_cast<float>(ZOrder::Z02Back10) });
		BackImageRenderer_[0]->SetImage("BackGround_Cigar.png");

		BackImageRenderer_[1] = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackImageRenderer_[1]->GetTransform()->SetLocalScaling(float4{ 2048.f,556.f });
		BackImageRenderer_[1]->GetTransform()->SetWorldPosition(float4{ 2048.f,-278.f ,static_cast<float>(ZOrder::Z02Back10) });
		BackImageRenderer_[1]->SetImage("BackGround_Cigar.png");


		Map::CurrentMap = CreateActor<Map>();
		// 1280 720
		Map::CurrentMap->GetCollisionMap()->SetImage("DicePalaceCol.png");
		Map::CurrentMap->GetCollisionMap()->GetTransform()->SetLocalScaling(float4{ 1440.f, 750.f });
		Map::CurrentMap->GetTransform()->SetWorldPosition(float4{ 720.f, -375.f, static_cast<float>(ZOrder::Z04CollisonMap01) });

		//Map::CurrentMap = CreateActor<Map>();
		//Map::CurrentMap->GetCollisionMap()->SetImage("DicePalaceCol.png");
		//Map::CurrentMap->GetCollisionMap()->GetTransform()->SetLocalScaling(float4{ 1280.f, 720.f });
		//Map::CurrentMap->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z04CollisonMap01) });
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition(float4(300.f, -487.0f, static_cast<float>(ZOrder::Z01Actor00Player01)));
	}

	{
		Mr_Wheezy_ = CreateActor<Mr_Wheezy>();
		Mr_Wheezy_->GetTransform()->SetWorldPosition(float4(1040.f, -60.f, static_cast<float>(ZOrder::Z02Back05)));

		AshImageRenderer_Left = Mr_Wheezy_->CreateTransformComponent<GameEngineImageRenderer>();
		AshImageRenderer_Left->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-Ash_Pale", 94, 102, 0.04f, false);
		AshImageRenderer_Left->SetChangeAnimation("Mr_Wheezy-Ash_Pale");
		AshImageRenderer_Left->SetCurAnimationFrame(101);
		AshImageRenderer_Left->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
		AshImageRenderer_Left->GetTransform()->SetWorldPosition(float4(240.f, -140.f, static_cast<float>(ZOrder::Z02Back04)));

		AshImageRenderer_Right = Mr_Wheezy_->CreateTransformComponent<GameEngineImageRenderer>();
		AshImageRenderer_Right->CreateAnimation("Mr_Wheezy.png", "Mr_Wheezy-Ash_Pale", 94, 102, 0.04f, false);
		AshImageRenderer_Right->SetChangeAnimation("Mr_Wheezy-Ash_Pale");
		AshImageRenderer_Right->SetCurAnimationFrame(102);
		AshImageRenderer_Right->GetTransform()->SetLocalScaling({ 550.f, 825.f, 1.0f });
		AshImageRenderer_Right->GetTransform()->SetWorldPosition(float4(1040.f, -140.f, static_cast<float>(ZOrder::Z02Back04)));
	}

	PhaseState_.ChangeState("Intro");

}
void Stage_Mr_Wheezy::LevelLoop_Update(float _DeltaTime)
{
	LevelLoadFadeUpdate(_DeltaTime);
	PhaseState_.Update(_DeltaTime);
}
void Stage_Mr_Wheezy::LevelLoop_End()
{
}


void Stage_Mr_Wheezy::LevelUpdate(float _DeltaTime)
{
	LoadState_.Update(_DeltaTime);

	if (true == GameEngineInput::GetInst().Down("FreeCameraOn"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}
}

void Stage_Mr_Wheezy::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}
void Stage_Mr_Wheezy::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	LoadState_.ChangeState("Init");
}

void Stage_Mr_Wheezy::ResourcesLoading_Start()
{
	
}
void Stage_Mr_Wheezy::ResourcesLoading_Update(float _DeltaTime)
{
}
void Stage_Mr_Wheezy::ResourcesLoading_End()
{
}

void Stage_Mr_Wheezy::Intro_Start()
{
}
void Stage_Mr_Wheezy::Intro_Update(float _DeltaTime)
{
	BlendRate_ -= _DeltaTime;
	if (0.f >= BlendRate_)
	{
		BlendRate_ = 0.f;

		PhaseState_.ChangeState("Playing");
		return;
	}

	FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });

}
void Stage_Mr_Wheezy::Intro_End()
{
}

void Stage_Mr_Wheezy::Playing_Start()
{
	//NextScene_ = "WorldMap";

	ReadyWALLOP();
}
void Stage_Mr_Wheezy::Playing_Update(float _DeltaTime)
{
	//if (true == IsStageMove_)
	//{
	//	KingDice_Marker_->Clear(StageMoveCount_);
	//}

	BackImageRenderer_[0]->GetTransform()->SetWorldMove(float4{ -_DeltaTime * 100.f ,0.f });
	BackImageRenderer_[1]->GetTransform()->SetWorldMove(float4{ -_DeltaTime * 100.f ,0.f });

	if (BackImageRenderer_[0]->GetTransform()->GetWorldPosition().x <= -1024.f)
	{
		BackImageRenderer_[0]->GetTransform()->SetWorldMove(float4{ 4096.f,0.f });
	}

	if (BackImageRenderer_[1]->GetTransform()->GetWorldPosition().x <= -1024.f)
	{
		BackImageRenderer_[1]->GetTransform()->SetWorldMove(float4{ 4096.f,0.f });
	}

	if (true == Victory_)
	{
		int ranint = Random_.RandomInt(-10, 10);

		GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f + ranint, static_cast<float>(ZOrder::Z00Camera00)));

		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 3.f)
		{
			BlendRate_ += _DeltaTime;
			FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
		}

		if (BlendRate_ >= 1.f)
		{
			BlendRate_ = 1.f;

#ifdef _DEBUG
			if (nullptr == GameEngineCore::LevelFind(NextScene_))
			{
				GameEngineDebug::MsgBoxError("존재하지 않는 레벨");
			}
#endif // _DEBUG
			dynamic_cast <LoaddingScene*>(GameEngineCore::LevelFind("LoaddingScene"))->SetLoaddingNextLevel(Stage_Mr_Wheezy::GetName(),NextScene_);;

			//GameEngineCore::LevelCreate<LoaddingScene>("Loading")->SetLoaddingNextLevel("Play");;
			GameEngineCore::LevelChange("LoaddingScene");
		}
	}
}
void Stage_Mr_Wheezy::Playing_End()
{
}


