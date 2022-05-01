#include "PreCompile.h"
#include "DicePaclace.h"
#include "LoaddingScene.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/MouseActor.h>
#include <GameEngine/GameEngineCore.h>
//#include <GameEngineBase/GameEngineRandom.h>

#include "UserGame.h"

#include "Map.h"
#include "Image.h"
#include "KingDice_Marker.h"
#include "Effect.h"
#include "PerryObjectDice.h"
#include "King_Dice.h"
#include "Player.h"

DicePaclace::DicePaclace() 
	: King_Dice_(nullptr)
	, PhaseState_(this)
{
}

DicePaclace::~DicePaclace() // default destructer 디폴트 소멸자
{
}

void DicePaclace::LevelResourcesLoad()
{
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

			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Knockout"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("ReadyWALLOP!"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("YouDied"));

			TextureDir.MoveChild("KingDice(Boss)");
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Clap"));

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
			TextureDir.MoveChild("KingDice(Boss)");

			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDIce-Idle"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDIce-Intro"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Defeat"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Chomp"));

			TextureDir.MoveChild("KDice-Attack");

			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Attack-Hand-Idle"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Attack-Hand-Birth"));

			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Attack-Body-Idle"));
			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Attack-Body-Birth"));

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

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
				}

				GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("ParryObjectDice.png");
				Texture->Cut(10, 8);
				Texture = GameEngineTextureManager::GetInst().Find("BossExplosion.png");
				Texture->Cut(10, 1);

			}
			TextureDir.MoveChild("DicePalaceMain_Numbers");
			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
				}
			}

			TextureDir.MoveParent("DicePalace");

			TextureDir.MoveChild("KingDice(Boss)");
			TextureDir.MoveChild("KDice-Attack");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
				}
				GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Card_Club.png");
				Texture->Cut(7, 3);

				Texture = GameEngineTextureManager::GetInst().Find("Card_Hraet.png");
				Texture->Cut(7, 3);
			}

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
			TextureDir.MoveChild("UI");

			std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

			for (size_t i = 0; i < AllFile.size(); i++)
			{
				GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
			}
			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Bottom_HP.png");
			Texture->Cut(6, 2);

			Texture = GameEngineTextureManager::GetInst().Find("BottomCard_Dia.png");
			Texture->Cut(6, 1);

			Texture = GameEngineTextureManager::GetInst().Find("BottomCard_Spade.png");
			Texture->Cut(6, 1);

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
			TextureDir.MoveChild("CharactorSprite");
			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
				}
			}

			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Cup.png");

			Texture->Cut(20, 20);
			Texture = GameEngineTextureManager::GetInst().Find("Cup_Dash.png");
			Texture->Cut(8, 1);
			Texture = GameEngineTextureManager::GetInst().Find("PlayerDust.png");
			Texture->Cut(20, 6);
			Texture = GameEngineTextureManager::GetInst().Find("DashDust.png");
			Texture->Cut(13, 1);
			Texture = GameEngineTextureManager::GetInst().Find("HitEffect.png");
			Texture->Cut(9, 3);
			Texture = GameEngineTextureManager::GetInst().Find("ParryEffect.png");
			Texture->Cut(9, 1);
			Texture = GameEngineTextureManager::GetInst().Find("LandDust.png");
			Texture->Cut(6, 1);

			TextureDir.MoveChild("Bullet");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
				}
			}

			Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default.png");
			Texture->Cut(8, 1);
			Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default_Birth.png");
			Texture->Cut(4, 1);
			Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default_Death.png");
			Texture->Cut(6, 1);

			UserGame::LoadingFolder--;
		}
	);

}
void DicePaclace::LevelStart()
{
	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Camera00)));

	PhaseState_.CreateState("Intro", &DicePaclace::Intro_Start, &DicePaclace::Intro_Update, &DicePaclace::Intro_End);
	PhaseState_.CreateState("Playing", &DicePaclace::Playing_Start, &DicePaclace::Playing_Update, &DicePaclace::Playing_End);
	PhaseState_.CreateState("ResourcesLoading", &DicePaclace::ResourcesLoading_Start, &DicePaclace::ResourcesLoading_Update, &DicePaclace::ResourcesLoading_End);

	PhaseState_.ChangeState("ResourcesLoading");
}
void DicePaclace::LevelUpdate(float _DeltaTime)
{
	PhaseState_.Update(_DeltaTime);

	if (true == GameEngineInput::GetInst().Down("FreeCameraOn"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}
}

void DicePaclace::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

	//if (std::string::npos != _NextLevel->GetName().find("World")
	//	&& std::string::npos != _NextLevel->GetName().find("Boss"))
	//{

	//	Player::MainPlayer->GetLevel()->SetLevelActorMove(_NextLevel, Player::MainPlayer);
	//}

	// MoveLevelActor("TitleLevel", "BossLevel");

}
void DicePaclace::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	//{
	//	Image* Back = CreateActor<Image>();
	//	Back->ImageSetImage("Loading_background.png");
	//	Back->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Fx01)));
	//	Back->ImageRenderer_-> GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
	//	Back->ImageRenderer_->SetResultColor(float4{1.f,1.f,1.f,0.3f});
	//

	//	Effect* Effect_ = CreateActor<Effect>();
	//	GameEngineImageRenderer* _GameEngineImageRenderer = Effect_->EffectAnimationFolderActor("ReadyWALLOP!", "ReadyWALLOP!", 0.04f, false);

	//	_GameEngineImageRenderer->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
	//	_GameEngineImageRenderer->SetEndCallBack("ReadyWALLOP!", std::bind(&Image::Death, Back));

	//	Effect_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
	//}
}

void DicePaclace::ResourcesLoading_Start()
{
}
void DicePaclace::ResourcesLoading_Update(float _DeltaTime)
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
			//MouseActor* Actor = CreateActor<MouseActor>();
			//Actor->GetUIRenderer()->SetRenderGroup(1000);  
		}

		{
			ScreenFx = CreateActor<Image>();
			ScreenFx->ImageCreateAnimationFolder("ScreenFx", "ScreenFx", 0.04f, true);
			ScreenFx->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Fx01)));
			ScreenFx->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
		}

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
			KingDice_Marker_ = CreateActor<KingDice_Marker>();
			KingDice_Marker_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back08) });
		}

		{
			Player_ = CreateActor<Player>();
			GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
			Player_->GetTransform()->SetWorldPosition(float4(300.f, -487.0f, static_cast<float>(ZOrder::Z01Actor00Player01)));
		}

		{
			King_Dice_ = CreateActor<King_Dice>();
			King_Dice_->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z01Actor03)));
		}

		PhaseState_.ChangeState("Intro");
	}
}
void DicePaclace::ResourcesLoading_End()
{
}

void DicePaclace::Intro_Start()
{
}
void DicePaclace::Intro_Update(float _DeltaTime)
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
void DicePaclace::Intro_End()
{
}

void DicePaclace::Playing_Start()
{
	//NextScene_ = "WorldMap";

	ReadyWALLOP();
}
void DicePaclace::Playing_Update(float _DeltaTime)
{
	if (true == IsStageMove_)
	{
		KingDice_Marker_->Clear(StageMoveCount_);
	}

	if (true == Victory_)
	{
		int ranint = Random_.RandomInt(-10,10);

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
void DicePaclace::Playing_End()
{
}

bool DicePaclace::ThreadResourceLoad()
{
//아직 안씀
	return true;
}

//void DicePaclace::ReadyWALLOP()
//{
//	Image* Back = CreateActor<Image>();
//	Back->ImageSetImage("Loading_background.png");
//	Back->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Fx01)));
//	Back->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
//	Back->ImageRenderer_->SetResultColor(float4{ 1.f,1.f,1.f,0.3f });
//
//	Effect* Effect_ = CreateActor<Effect>();
//	GameEngineImageRenderer* _GameEngineImageRenderer = Effect_->EffectAnimationFolderActor("ReadyWALLOP!", "ReadyWALLOP!", 0.04f, false);
//
//	_GameEngineImageRenderer->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
//	_GameEngineImageRenderer->SetEndCallBack("ReadyWALLOP!", std::bind(&Image::Death, Back));
//
//	Effect_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
//}
//void DicePaclace::KnockoutEnd()
//{
//	GameEngineCore::SetTimeRate(1.f);
//
//	Victory_ = true;
//}
//void DicePaclace::Knockout()
//{
//	Player_->SetVictory();
//
//	Effect* Effect_ = CreateActor<Effect>();
//
//	GameEngineCore::SetTimeRate	(0.0001f);
//	Effect_->SetPlayRate		(10000.f);
//
//	GameEngineImageRenderer* _GameEngineImageRenderer = Effect_->EffectAnimationFolderActor("Knockout", "Knockout", 0.04f, false);
//	_GameEngineImageRenderer->SetEndCallBack("Knockout", std::bind(&Image::Death, Effect_));
//	_GameEngineImageRenderer->SetEndCallBack("Knockout", std::bind(&DicePaclace::KnockoutEnd, this));
//
//	_GameEngineImageRenderer->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
//
//	Effect_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
//}