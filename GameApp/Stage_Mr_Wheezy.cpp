#include "Precompile.h"
#include "Stage_Mr_Wheezy.h"
#include "DicePaclace.h"

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
#include "Flying_Cigar.h"

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

	PhaseState_.CreateState("Intro", &Stage_Mr_Wheezy::Intro_Start, &Stage_Mr_Wheezy::Intro_Update, &Stage_Mr_Wheezy::Intro_End);
	PhaseState_.CreateState("Playing", &Stage_Mr_Wheezy::Playing_Start, &Stage_Mr_Wheezy::Playing_Update, &Stage_Mr_Wheezy::Playing_End);

	LoadState_.CreateState("ResourcesLoad", &Stage_Mr_Wheezy::ResourcesLoad_Start, &Stage_Mr_Wheezy::ResourcesLoad_Update, nullptr);
	LoadState_.CreateState("Init", nullptr, &Stage_Mr_Wheezy::Init_Update, nullptr);
	LoadState_.CreateState("LevelLoop", &Stage_Mr_Wheezy::LevelLoop_Start, &Stage_Mr_Wheezy::LevelLoop_Update, nullptr);
}
void Stage_Mr_Wheezy::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	LoadState_.ChangeState("Init");
}

void Stage_Mr_Wheezy::LevelUpdate(float _DeltaTime)
{
	LoadState_.Update(_DeltaTime);
}

void Stage_Mr_Wheezy::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
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
			TextureDir.MoveChild("CommonEffect");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}
			}

			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("BossExplosion.png");
			Texture->Cut(10, 1);

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

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}
			}

			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("Intro_Flame.png");

			Texture->Cut(10, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes( "Intro_Hand.png");
			Texture->Cut(14, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Mr_Wheezy.png");
			Texture->Cut(20, 6);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Smoke_FX_Front.png");
			Texture->Cut(17, 2);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Smoke_FX_Back.png");
			Texture->Cut(12, 2);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Fly_cigar.png");
			Texture->Cut(10, 2);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Wheezy_Fire.png");
			Texture->Cut(3, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Wheezy_Fire_Cloud.png");
			Texture->Cut(16, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Cigar_dust.png");
			Texture->Cut(9, 1);

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

			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("BG_top_smoke"));

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}
			}

			TextureDir.MoveChild("BG_Fire");
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("BG_Fire_Back"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("BG_Fire_Front"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("BG_Fire_Middle"));
			
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
			HourGlass_->Death();
			HourGlass_ = nullptr;
			LoadState_.ChangeState("LevelLoop");
		}

		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
	}
}

void Stage_Mr_Wheezy::LevelLoop_Start()
{
	PhaseState_.ChangeState("Intro");

	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	FadeImage_->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00)));

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Camera00)));

	GameEngineActor* BackImage = CreateActor<GameEngineActor>();
	GameEngineImageRenderer* BackRenderer;
	{
		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1320.f,732.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-360.f,static_cast<float>(ZOrder::Z02Back01) });
		BackRenderer->CreateLevelAnimationFolder("BG_top_smoke", "BG_top_smoke", 0.04f);
		BackRenderer->SetChangeAnimation("BG_top_smoke");
		BackRenderer->SetResultColor(float4{ 1.f, 1.f, 1.f, 0.5f });

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 312.f,277.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 1180,-600,static_cast<float>(ZOrder::Z02Back01) });
		BackRenderer->SetLevelImage("kd_cigar_bg_smoke_fg.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1500.f,750.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-450.f,static_cast<float>(ZOrder::Z02Back02) });
		BackRenderer->CreateLevelAnimationFolder("BG_Fire_Front", "BG_Fire_Front", 0.04f);
		BackRenderer->SetChangeAnimation("BG_Fire_Front");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,360.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 240.f,-550.f,static_cast<float>(ZOrder::Z02Back03) });
		BackRenderer->SetLevelImage("Ashtray_left_fr.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,360.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 1040.f,-550.f,static_cast<float>(ZOrder::Z02Back03) });
		BackRenderer->SetLevelImage("Ashtray_right_fr.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,360.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 240.f,-550.f,static_cast<float>(ZOrder::Z02Back07) });
		BackRenderer->SetLevelImage("Ashtray_left_bk.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 500.f,360.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 1040.f,-550.f,static_cast<float>(ZOrder::Z02Back07) });
		BackRenderer->SetLevelImage("Ashtray_right_bk.png");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1500.f,750.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-375.f,static_cast<float>(ZOrder::Z02Back08) });
		BackRenderer->CreateLevelAnimationFolder("BG_Fire_Middle", "BG_Fire_Middle", 0.04f);
		BackRenderer->SetChangeAnimation("BG_Fire_Middle");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1500.f,750.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-300.f,static_cast<float>(ZOrder::Z02Back09) });
		BackRenderer->CreateLevelAnimationFolder("BG_Fire_Back", "BG_Fire_Back", 0.04f);
		BackRenderer->SetChangeAnimation("BG_Fire_Back");

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1379.f,720.f });
		BackRenderer->GetTransform()->SetLocalPosition(float4{ 640.f,-360.f,static_cast<float>(ZOrder::Z02Back10) });
		BackRenderer->SetLevelImage("Mr_Wheezy_Back.png");
	}

	{
		BackImageRenderer_[0] = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackImageRenderer_[0]->GetTransform()->SetLocalScaling(float4{ 2048.f,556.f });
		BackImageRenderer_[0]->GetTransform()->SetWorldPosition(float4{ 0.f,-278.f,static_cast<float>(ZOrder::Z02Back11) });
		BackImageRenderer_[0]->SetLevelImage("BackGround_Cigar.png");

		BackImageRenderer_[1] = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackImageRenderer_[1]->GetTransform()->SetLocalScaling(float4{ 2048.f,556.f });
		BackImageRenderer_[1]->GetTransform()->SetWorldPosition(float4{ 2048.f,-278.f ,static_cast<float>(ZOrder::Z02Back11) });
		BackImageRenderer_[1]->SetLevelImage("BackGround_Cigar.png");
	}

	{
		// 1280 720
		Map::CurrentMap = CreateActor<Map>();
		Map::CurrentMap->GetCollisionMap()->SetLevelImage("Mr_WheezyCol.png");
		Map::CurrentMap->GetCollisionMap()->GetTransform()->SetLocalScaling(float4{ 1280.f, 720.f });
		Map::CurrentMap->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z04CollisonMap01) });
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition(float4(300.f, -487.0f, static_cast<float>(ZOrder::Z02Back05)));
	}

	{
		Mr_Wheezy_ = CreateActor<Mr_Wheezy>();

		Flying_Cigar_ = CreateActor<Flying_Cigar>();
		Flying_Cigar_->GetTransform()->SetWorldPosition(float4(640.f, -460.f, static_cast<float>(ZOrder::Z02Back06)));
	}

	{
		Effect* IntroEffect = CreateActor<Effect>();
		IntroEffect->EffectAnimationActor("Intro_Hand.png", "Intro_Hand", float4{498.f,506.f}, 0, 13, 0.07142f, false);
		IntroEffect->GetTransform()->SetWorldPosition(float4(625.f, -87.f, static_cast<float>(ZOrder::Z02Back06)));
	} 

	{
		Effect* IntroEffect = CreateActor<Effect>();
		IntroEffect->EffectAnimationActor("Intro_Flame.png", "Intro_Flame", float4{ 186.f,288.f }, 0, 9, 0.07142f, false);
		IntroEffect->GetTransform()->SetWorldPosition(float4(917.f, 21.5, static_cast<float>(ZOrder::Z02Back06)));
	}
	PhaseState_.ChangeState("Intro");

}
void Stage_Mr_Wheezy::LevelLoop_Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("FreeCameraOn"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}

	LevelLoadFadeUpdate(_DeltaTime);

	PhaseState_.Update(_DeltaTime);
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
	ReadyWALLOP();
}
void Stage_Mr_Wheezy::Playing_Update(float _DeltaTime)
{
	{
		Flying_Cigar_->GetTransform()->SetWorldMove(float4{ 0.f,300.f * _DeltaTime });
		if (Flying_Cigar_->GetTransform()->GetWorldPosition().y >= 360)
		{
			Flying_Cigar_->GetTransform()->SetWorldPosition(float4(640.f, -650, static_cast<float>(ZOrder::Z02Back05)));
		}

		BackImageRenderer_[0]->GetTransform()->SetWorldMove(float4{ -_DeltaTime * 100.f ,0.f });
		if (BackImageRenderer_[0]->GetTransform()->GetWorldPosition().x <= -1024.f)
		{
			BackImageRenderer_[0]->GetTransform()->SetWorldMove(float4{ 4096.f,0.f });
		}

		BackImageRenderer_[1]->GetTransform()->SetWorldMove(float4{ -_DeltaTime * 100.f ,0.f });
		if (BackImageRenderer_[1]->GetTransform()->GetWorldPosition().x <= -1024.f)
		{
			BackImageRenderer_[1]->GetTransform()->SetWorldMove(float4{ 4096.f,0.f });
		}
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

			UserGame::StageInfo_.Dice_ClearStage_[0] = true;
			UserGame::StageInfo_.Dice_ClearStage_[1] = true;
			UserGame::StageInfo_.Dice_ClearStage_[2] = true;

			GameEngineCore::LevelCreate<DicePaclace>("DicePaclace");

			GameEngineCore::LevelChange("DicePaclace");
		}
	}
}
void Stage_Mr_Wheezy::Playing_End()
{	

}


