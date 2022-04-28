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
{
}

Stage_Mr_Wheezy::~Stage_Mr_Wheezy()
{
}

void Stage_Mr_Wheezy::LevelResourcesLoad()
{
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

			TextureDir.MoveChild("BackGround");

			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("BG_top_smoke"));

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
				}
			}

			TextureDir.MoveChild("BG_Fire");
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("BG_Fire_Back"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("BG_Fire_Front"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("BG_Fire_Middle"));
		}
}
void Stage_Mr_Wheezy::LevelStart()
{
	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Camera00)));

	PhaseState_.CreateState("Intro", &Stage_Mr_Wheezy::Intro_Start, &Stage_Mr_Wheezy::Intro_Update, &Stage_Mr_Wheezy::Intro_End);
	PhaseState_.CreateState("Playing", &Stage_Mr_Wheezy::Playing_Start, &Stage_Mr_Wheezy::Playing_Update, &Stage_Mr_Wheezy::Playing_End);
	PhaseState_.CreateState("ResourcesLoading", &Stage_Mr_Wheezy::ResourcesLoading_Start, &Stage_Mr_Wheezy::ResourcesLoading_Update, &Stage_Mr_Wheezy::ResourcesLoading_End);

	PhaseState_.ChangeState("ResourcesLoading");
}
void Stage_Mr_Wheezy::LevelUpdate(float _DeltaTime)
{
	PhaseState_.Update(_DeltaTime);

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
}

void Stage_Mr_Wheezy::ResourcesLoading_Start()
{
}
void Stage_Mr_Wheezy::ResourcesLoading_Update(float _DeltaTime)
{
	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		CreateActorCheck = true;

		GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

		GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
		GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Camera00)));

		{
			BlendRate_ = 1.f;

			FadeImage_ = CreateActor<Image>();

			FadeImage_->ImageRenderer_->SetImage("title_screen_background.png");
			FadeImage_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
			FadeImage_->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f });
			FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
		}

		{
			//Image* BackImage = CreateActor<Image>();
			//BackImage->ImageSetImage("DicePalaceBack.png");
			//BackImage->ImageRenderer_->SetAdjustImzgeSize();
			//BackImage->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back10) });

			//BackImage = CreateActor<Image>();
			//BackImage->ImageSetImage("DicePalaceMain.png");
			//BackImage->ImageRenderer_->SetAdjustImzgeSize();
			//BackImage->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back09) });

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
			Mr_Wheezy_->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z01Actor03)));
		}

		PhaseState_.ChangeState("Intro");
	}
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
	if (true == IsStageMove_)
	{
		KingDice_Marker_->Clear(StageMoveCount_);
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
			dynamic_cast <LoaddingScene*>(GameEngineCore::LevelFind("LoaddingScene"))->SetLoaddingNextLevel(NextScene_);;

			//GameEngineCore::LevelCreate<LoaddingScene>("Loading")->SetLoaddingNextLevel("Play");;
			GameEngineCore::LevelChange("LoaddingScene");
		}
	}
}
void Stage_Mr_Wheezy::Playing_End()
{
}

void Stage_Mr_Wheezy::ReadyWALLOP()
{
	Image* Back = CreateActor<Image>();
	Back->ImageSetImage("Loading_background.png");
	Back->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Fx01)));
	Back->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
	Back->ImageRenderer_->SetResultColor(float4{ 1.f,1.f,1.f,0.3f });

	Effect* Effect_ = CreateActor<Effect>();
	GameEngineImageRenderer* _GameEngineImageRenderer = Effect_->EffectAnimationFolderActor("ReadyWALLOP!", "ReadyWALLOP!", 0.04f, false);

	_GameEngineImageRenderer->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
	_GameEngineImageRenderer->SetEndCallBack("ReadyWALLOP!", std::bind(&Image::Death, Back));

	Effect_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
}

void Stage_Mr_Wheezy::KnockoutEnd()
{
	GameEngineCore::SetTimeRate(1.f);

	Victory_ = true;
}

void Stage_Mr_Wheezy::Knockout()
{
	Player_->SetVictory();

	Effect* Effect_ = CreateActor<Effect>();

	GameEngineCore::SetTimeRate(0.0001f);
	Effect_->SetPlayRate(10000.f);

	GameEngineImageRenderer* _GameEngineImageRenderer = Effect_->EffectAnimationFolderActor("Knockout", "Knockout", 0.04f, false);
	_GameEngineImageRenderer->SetEndCallBack("Knockout", std::bind(&Image::Death, Effect_));
	_GameEngineImageRenderer->SetEndCallBack("Knockout", std::bind(&Stage_Mr_Wheezy::KnockoutEnd, this));

	_GameEngineImageRenderer->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });

	Effect_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
}

