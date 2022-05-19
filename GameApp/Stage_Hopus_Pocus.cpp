#include "Precompile.h"
#include "Stage_Hopus_pocus.h"
#include "Hopus_pocus.h"
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

Stage_Hopus_pocus::Stage_Hopus_pocus()
	: PhaseState_(this)
	, LoadState_(this)
	, Hopus_pocus_(nullptr)
	, Floating_Card_(nullptr)
	, BackRightImageRenderer_{nullptr}
	, LightBlendRate_{ { 1.f,1.f,1.f,1.f } }
	, LightBlendCheck_(false)
{
}

Stage_Hopus_pocus::~Stage_Hopus_pocus()
{
}

void Stage_Hopus_pocus::LevelStart()
{
	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	PhaseState_.CreateState("Intro", &Stage_Hopus_pocus::Intro_Start, &Stage_Hopus_pocus::Intro_Update, &Stage_Hopus_pocus::Intro_End);
	PhaseState_.CreateState("Playing", &Stage_Hopus_pocus::Playing_Start, &Stage_Hopus_pocus::Playing_Update, &Stage_Hopus_pocus::Playing_End);

	LoadState_.CreateState("ResourcesLoad", &Stage_Hopus_pocus::ResourcesLoad_Start, &Stage_Hopus_pocus::ResourcesLoad_Update, nullptr);
	LoadState_.CreateState("Init", nullptr, &Stage_Hopus_pocus::Init_Update, nullptr);
	LoadState_.CreateState("LevelLoop", &Stage_Hopus_pocus::LevelLoop_Start, &Stage_Hopus_pocus::LevelLoop_Update, nullptr);
}
void Stage_Hopus_pocus::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	LoadState_.ChangeState("Init");
}

void Stage_Hopus_pocus::LevelUpdate(float _DeltaTime)
{
	LoadState_.Update(_DeltaTime);
}

void Stage_Hopus_pocus::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}

void Stage_Hopus_pocus::Init_Update(float _DeltaTime)
{
	LoadState_.ChangeState("ResourcesLoad");
}

void Stage_Hopus_pocus::ResourcesLoad_Start()
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
			TextureDir.MoveChild("Hopus_Pocus");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}
			}

			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("Rabit_Skull.png");

			Texture->Cut(11, 2);

			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("Hopus_Pocus_Attack"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("Hopus_Pocus_Death"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("Hopus_Pocus_Idle"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("Hopus_Pocus_Intro"));


			TextureDir.MoveChild("BackGround");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}
			}

			UserGame::LoadingFolder--;
		}
	);

	ResourcesLoadFadeInit();
}
void Stage_Hopus_pocus::ResourcesLoad_Update(float _DeltaTime)
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

void Stage_Hopus_pocus::LevelLoop_Start()
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
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1540.f,842.f });
		BackRenderer->SetLevelImage("Hopus_Back_6.png");
		BackRenderer->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z02Back15)));

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1540.f,842.f });
		BackRenderer->SetLevelImage("Hopus_Back_5_floar.png");
		BackRenderer->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z02Back14)));

		BackRightImageRenderer_[0] = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRightImageRenderer_[0]->GetTransform()->SetLocalScaling(float4{ 1540.f,842.f });
		BackRightImageRenderer_[0]->SetLevelImage("Hopus_Back_4_Blue.png");
		BackRightImageRenderer_[0]->SetResultColor(float4{1.f,1.f,1.f,1.f});
		BackRightImageRenderer_[0]->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z02Back13)));

		BackRightImageRenderer_[1] = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRightImageRenderer_[1]->GetTransform()->SetLocalScaling(float4{ 1540.f,842.f });
		BackRightImageRenderer_[1]->SetLevelImage("Hopus_Back_3_Bright.png");
		BackRightImageRenderer_[1]->SetResultColor(float4{1.f,1.f,1.f,1.f});
		BackRightImageRenderer_[1]->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z02Back12)));

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1540.f,842.f });
		BackRenderer->SetLevelImage("Hopus_Back_2.png");
		BackRenderer->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z02Back11)));

		Hopus_pocus_ = CreateActor<Hopus_pocus>();
		Hopus_pocus_->GetTransform()->SetWorldPosition(float4(1040.f, -360.f, static_cast<float>(ZOrder::Z02Back10)));

		BackRenderer = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
		BackRenderer->GetTransform()->SetLocalScaling(float4{ 1540.f,842.f });
		BackRenderer->SetLevelImage("Hopus_Back_1.png");
		BackRenderer->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z02Back09)));
	}

	{
		// 1280 720
		Map::CurrentMap = CreateActor<Map>();
		Map::CurrentMap->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z04CollisonMap01) });
		Map::CurrentMap->GetCollisionMap()->GetTransform()->SetLocalScaling(float4{ 1356.f, 720.f });
		Map::CurrentMap->GetCollisionMap()->SetLevelImage("Rabbit_Background_col.png");
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition(float4(300.f, -487.0f, static_cast<float>(ZOrder::Z00PlayerFront00)));
	}

	PhaseState_.ChangeState("Intro");
}
void Stage_Hopus_pocus::LevelLoop_Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("FreeCameraOn"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}

	LevelLoadFadeUpdate(_DeltaTime);

	PhaseState_.Update(_DeltaTime);
}

void Stage_Hopus_pocus::Intro_Start()
{
}
void Stage_Hopus_pocus::Intro_Update(float _DeltaTime)
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
void Stage_Hopus_pocus::Intro_End()
{
}

void Stage_Hopus_pocus::Playing_Start()
{
	ReadyWALLOP();
}
void Stage_Hopus_pocus::Playing_Update(float _DeltaTime)
{
	{
		if (true == LightBlendCheck_)
		{
			LightBlendRate_[0].a -= _DeltaTime;

			if (LightBlendRate_[0].a < 0.f)
			{
				LightBlendRate_[0].a = 0.f;
				LightBlendCheck_ = false;
			}

		}
		else
		{
			LightBlendRate_[0].a += _DeltaTime;

			if (LightBlendRate_[0].a > 1.f)
			{
				LightBlendRate_[0].a = 1.f;
				LightBlendCheck_ = true;
			}
		}

		LightBlendRate_[1] = LightBlendRate_[0];
		LightBlendRate_[1].a = 1.f - LightBlendRate_[1].a;

		BackRightImageRenderer_[0]->SetResultColor(LightBlendRate_[0]);
		BackRightImageRenderer_[1]->SetResultColor(LightBlendRate_[1]);
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

			UserGame::StageInfo_.Dice_ClearStage_[4] = true;

			GameEngineCore::LevelCreate<DicePaclace>("DicePaclace");

			GameEngineCore::LevelChange("DicePaclace");
		}
	}
}
void Stage_Hopus_pocus::Playing_End()
{	

}


