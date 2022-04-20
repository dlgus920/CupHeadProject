#include "PreCompile.h"
#include "DicePaclace.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/MouseActor.h>

#include "Map.h"
#include "Image.h"
#include "PerryObjectDice.h"
#include "King_Dice.h"
#include "Player.h"

DicePaclace::DicePaclace() // default constructer 디폴트 생성자
{

}

DicePaclace::~DicePaclace() // default destructer 디폴트 소멸자
{

}

void DicePaclace::LevelResourcesLoad()
{
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
		TextureDir.MoveChild("KingDice(Boss)");

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDIce-Idle"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDIce-Intro"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Defeat"));

		//TextureDir.MoveParent("DicePalace");
		TextureDir.MoveChild("KDice-Attack");

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Attack-Hand-Idle"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Attack-Hand-Birth"));

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Attack-Body-Idle"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDice-Attack-Body-Birth"));

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
	}

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
	}

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
	}
}

void DicePaclace::LevelStart()
{
	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Camera00)));

	{
		//MouseActor* Actor = CreateActor<MouseActor>();
		//Actor->GetUIRenderer()->SetRenderGroup(1000);  
	}

	{
		Image* BackImage = CreateActor<Image>();
		BackImage->ImageSetImage("DicePalaceBack.png");
		BackImage->SetAdjustImzgeSize();
		BackImage->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back10) });

		BackImage = CreateActor<Image>();
		BackImage->ImageSetImage("DicePalaceMain.png");
		BackImage->SetAdjustImzgeSize();
		BackImage->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z02Back09) });

		Map* _Map = CreateActor<Map>();

		// 1280 720
		_Map->GetCollisionMap()->SetImage("DicePalaceCol.png");
		_Map->GetCollisionMap()->GetTransform()->SetLocalScaling(float4{ 1280.f, 720.f });
		_Map->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z04CollisonMap01) });
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition(float4(900.f, -400.0f, static_cast<float>(ZOrder::Z01Actor00Player01)));
	}

	{
		King_Dice_ = CreateActor<King_Dice>();
		King_Dice_->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z01Actor03)));
	}
}

void DicePaclace::LevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("FreeCameraOn"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}
}

void DicePaclace::LevelChangeEndEvent()
{
}

void DicePaclace::LevelChangeStartEvent()
{
}
