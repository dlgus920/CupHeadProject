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
		TextureDir.MoveChild("Monster");
		TextureDir.MoveChild("KingDice(Boss)");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}

		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("ParryObjectDice.png");
		Texture->Cut(10, 8);

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDIce-Idle"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("KDIce-Intro"));
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("CharactorSprite");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}
		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Cup.png");
		Texture->Cut(20, 20);
		Texture = GameEngineTextureManager::GetInst().Find("Cup_Dash.png");
		Texture->Cut(8, 1);
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Bullet");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}
		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default.png");
		Texture->Cut(8, 1);
		Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default_Birth.png");
		Texture->Cut(4, 1);
		Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default_Death.png");
		Texture->Cut(6, 1);
	}

}

void DicePaclace::LevelStart()
{
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

		//_Map->MapImage_ = _Map->CreateTransformComponent<GameEngineImageRenderer>();
		//_Map->MapImage_->SetImage("DicePalaceMain.png");
		//_Map->MapImage_->GetTransform()->SetLocalScaling(1280.f, 720.f);
		////_Map->MapImage_->SetAdjustImzgeSize();

		// 1280 720
		_Map->GetCollisionMap()->SetImage("DicePalaceCol.png");
		_Map->GetCollisionMap()->GetTransform()->SetLocalScaling(1280.f, 720.f);

		_Map->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z04CollisonMap01) });



		//_Map->SetMapImage("DicePalaceMain.png", "DicePalaceCol.png");
		// 
		//_Map->SetMapImage("WorldMap_Background.png", "WorldMap_PixelCheckBackground.png", 1212, -939.5);
		//_Map->GetTransform()->SetWorldPosition(float4{ 1200.f, -1000.f, static_cast<int>(ZOrder::Z04CollisonMap00) });
		//_Map->GetTransform()->SetWorldPosition(float4{ 0.f, 0.f, 100.0f });
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition(float4(900.f, -400.0f, static_cast<float>(ZOrder::Z01Actor00Player01)));
	}

	{
		King_Dice* Actor = CreateActor<King_Dice>();
		//Actor->GetTransform()->SetWorldPosition(float4(670.f, -120.f, static_cast<float>(ZOrder::Z01Actor03)));
		Actor->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z01Actor03)));
		//float4 texsize = Actor->GetTextureSize();
		//float4 cutsize = Actor->GetCutSize();
		//float4 TextureScale = Actor->GetTextureScale();
	}
	{
		PerryObjectDice* PerryDice = CreateActor<PerryObjectDice>();
		PerryDice ->GetTransform()->SetWorldPosition(float4(900.f, -400.0f, static_cast<float>(ZOrder::Z01Actor02)));
	}

	//{
	//	TopUI* Actor = CreateActor<TopUI>();
	//	Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	//}
}

void DicePaclace::LevelUpdate(float _DeltaTime)
{
}

void DicePaclace::LevelChangeEndEvent()
{
}

void DicePaclace::LevelChangeStartEvent()
{
}
