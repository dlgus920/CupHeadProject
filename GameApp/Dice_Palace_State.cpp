#include "PreCompile.h"
#include "DicePaclace.h"
#include "LoaddingScene.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/MouseActor.h>
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineImageRenderer.h>
//#include <GameEngineBase/GameEngineRandom.h>

#include "UserGame.h"

#include "Map.h"
#include "Image.h"
#include "KingDice_Marker.h"
#include "Effect.h"
#include "PerryObjectDice.h"
#include "King_Dice.h"
#include "Player.h"

void DicePaclace::Init_Update(float _DeltaTime) 
{
	LoadState_.ChangeState("ResourcesLoad");
}

void DicePaclace::ResourcesLoad_Start()
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
			TextureDir.MoveChild("KingDice(Boss)");

			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDice-Clap"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDIce-Idle"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDIce-Intro"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDice-Defeat"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDice-Chomp"));

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
			TextureDir.MoveChild("KDice-Attack");

			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDice-Attack-Hand-Idle"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDice-Attack-Hand-Birth"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDice-Attack-Body-Idle"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("KDice-Attack-Body-Birth"));

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
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}

				GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("ParryObjectDice.png");
				Texture->Cut(10, 8);
			}

			TextureDir.MoveChild("CommonEffect");
			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}

				GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("BossExplosion.png");
				Texture->Cut(10, 1);
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
			TextureDir.MoveChild("DicePalace");
			TextureDir.MoveChild("DicePalaceMain_Numbers");

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
			TextureDir.MoveChild("KDice-Attack");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}
				GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("Card_Club.png");
				Texture->Cut(7, 3);

				Texture = GameEngineTextureManager::GetInst().FindLevelRes("Card_Hraet.png");
				Texture->Cut(7, 3);
			}

			UserGame::LoadingFolder--;
		}
	);

	ResourcesLoadFadeInit();
}
void DicePaclace::ResourcesLoad_Update(float _DeltaTime) 
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

void DicePaclace::LevelLoop_Start() 
{
	PhaseState_.ChangeState("Intro");

	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	FadeImage_->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00)));

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Camera00)));

	//{
	//	ScreenFx = CreateActor<Image>();
	//	ScreenFx->ImageCreateAnimationFolder("ScreenFx", "ScreenFx", 0.04f, true);
	//	ScreenFx->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Fx01)));
	//	ScreenFx->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
	//}

	{
		Image* BackImage = CreateActor<Image>();
		BackImage->ImageRenderer_->SetLevelImage("DicePalaceBack.png");
		BackImage->ImageRenderer_->SetAdjustImzgeSize();
		BackImage->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back10) });

		BackImage = CreateActor<Image>();
		BackImage->ImageRenderer_->SetLevelImage("DicePalaceMain.png");
		BackImage->ImageRenderer_->SetAdjustImzgeSize();
		BackImage->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back09) });

		for (int i = 0; i < 11; ++i)
		{
			NumRenderer_[i] = BackImage->CreateTransformComponent<GameEngineImageRenderer>();
			NumRenderer_[i]->GetTransform()->SetLocalScaling(float4{870.4,400.f});

			if (false == UserGame::StageInfo_.Dice_ClearStage_[i])
			{
				std::string str;

				if (i < 9)
				{
					str = "Num_00";
				}
				else
				{
					str = "Num_0";
				}

				std::string numstr = std::to_string(i+1);

				str += numstr;
				str += ".png";

				NumRenderer_[i]->SetLevelImage(str);
				NumRenderer_[i]->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back09) });
			}
			else
			{
				std::string str;
				if (i < 9)
				{
					str = "Clear_00";
				}
				else
				{
					str = "Clear_0";
				}

				std::string numstr = std::to_string(i+1);

				str += numstr;
				str += ".png";

				NumRenderer_[i]->SetLevelImage(str);
				NumRenderer_[i]->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back09) });
			}
		}

		Map::CurrentMap = CreateActor<Map>();
		// 1280 720
		Map::CurrentMap->GetCollisionMap()->SetLevelImage("DicePalaceCol.png");
		Map::CurrentMap->GetCollisionMap()->GetTransform()->SetLocalScaling(float4{ 1440.f, 750.f });
		Map::CurrentMap->GetTransform()->SetWorldPosition(float4{ 720.f, -375.f, static_cast<float>(ZOrder::Z04CollisonMap01) });

		//Map::CurrentMap = CreateActor<Map>();
		//Map::CurrentMap->GetCollisionMap()->SetImage("DicePalaceCol.png");
		//Map::CurrentMap->GetCollisionMap()->GetTransform()->SetLocalScaling(float4{ 1280.f, 720.f });
		//Map::CurrentMap->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z04CollisonMap01) });
	}

	//{
	//	KingDice_Marker_ = CreateActor<KingDice_Marker>();
	//	KingDice_Marker_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back08) });
	//}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition(float4(300.f, -487.0f, static_cast<float>(ZOrder::Z01Actor00Player01)));
	}

	{
		King_Dice_ = CreateActor<King_Dice>();
		//King_Dice_->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z01Actor03)));
	}

}
void DicePaclace::LevelLoop_Update(float _DeltaTime) 
{
	PhaseState_.Update(_DeltaTime);
}



