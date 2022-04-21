#include "PreCompile.h"
#include "WorldMapScene.h"

#include "LoaddingScene.h"
#include "DicePaclace.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/MouseActor.h>

#include "Image.h"
#include "Map.h"
#include "Object.h"
#include "StagePoint.h"
#include "WorldMapPlayer.h"


WorldMapScene::WorldMapScene() // default constructer 디폴트 생성자
{

}

WorldMapScene::~WorldMapScene() // default destructer 디폴트 소멸자
{

}

void WorldMapScene::LevelResourcesLoad()
{
	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("World");
		TextureDir.MoveChild("Background");

		{
			std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

			for (size_t i = 0; i < AllFile.size(); i++)
			{
				GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
			}
		}

		TextureDir.MoveParent("World");
		TextureDir.MoveChild("Cuphead");
		{
			std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

			for (size_t i = 0; i < AllFile.size(); i++)
			{
				GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
			}
			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("WorldCuphead.png");
			Texture->Cut(16, 8);

			Texture = GameEngineTextureManager::GetInst().Find("Dust.png");
			Texture->Cut(20, 6);
		}

	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Loading");

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("ScreenIris"));
	}
}

void WorldMapScene::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

	{
		//MouseActor* Actor = CreateActor<MouseActor>();
		//Actor->GetUIRenderer()->SetRenderGroup(1000);  
	}

	{
		// 1280 720
		Map* _Map = CreateActor<Map>();
		_Map->GetCollisionMap()->SetImage("WorldMap_PixelCheckBackground.png");
		_Map->GetCollisionMap()->SetAdjustImzgeSize();
		_Map->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z04CollisonMap00) });

		Image* MapImage = CreateActor<Image>();
		MapImage ->ImageSetImage("WorldMap_Background.png");
		MapImage ->ImageRenderer_->SetAdjustImzgeSize();
		MapImage ->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z02Back10) });
	}

	{
		StagePoint* WorldMapPoint = CreateActor<StagePoint>();
		WorldMapPoint->GetTransform()->SetWorldPosition(float4{ 500.f, -1000.f, static_cast<int>(ZOrder::Z01Actor02) });

		WorldMapPoint->SetNextScene("DicePaclace");
	}

	{
		WorldMapPlayer_ = CreateActor<WorldMapPlayer>();
		WorldMapPlayer_->GetTransform()->SetWorldPosition(float4(500, -800.0f, static_cast<int>(ZOrder::Z01Actor00Player01)));
		GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
	}

	//{
	//	TopUI* Actor = CreateActor<TopUI>();
	//	Actor->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	//}
	{
		GameEngineCore::LevelCreate<DicePaclace>("DicePaclace");

	}
	{
		IrisImage_ = CreateActor<Image>();
		IrisImage_->ImageRenderer_->CreateAnimationFolder("ScreenIris", "ScreenIris_In", 0.055f, false);
		IrisImage_->ImageRenderer_->CreateAnimationFolder("ScreenIris", "ScreenIris_Out", 0.055f, false);
		IrisImage_->ImageRenderer_->SetAnimationReverse("ScreenIris_Out");


		//IrisImage_->ImageRenderer_->SetEndCallBack("ScreenIris", std::bind(&Image::Death, this));
		IrisImage_->ImageRenderer_->SetEndCallBack("ScreenIris_Out", std::bind(&WorldMapScene::ScreenFadeEnd, this));

		IrisImage_->GetTransform()->SetLocalScaling(float4{ 1280.f, 720.f });
		IrisImage_->GetTransform()->SetWorldPosition(float4{ 0.f,0.f,0.f,100.f });

		IrisImage_->ImageRenderer_->Off();
		//IrisImage_->ImageRenderer_->SetResultColor(float4{ 1.f,1.f,1.f,0.f });
	}
}

void WorldMapScene::LevelUpdate(float _DeltaTime)
{
	GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
}

void WorldMapScene::LevelChangeEndEvent()
{
	//릴리즈 맵
}

void WorldMapScene::LevelChangeStartEvent()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

	SetScreenIris(false);
	
	WorldMapPlayer_->Entry();

}

void WorldMapScene::ChangeScene(std::string _Scene)
{
	NextScene_ = _Scene;
	SetScreenIris(true);
}

void WorldMapScene::SetScreenIris(bool _In)
{
	IrisImage_->ImageRenderer_->On();

	float4 pos = GetMainCamera()->GetTransform()->GetWorldPosition();

	if (false == _In)
	{
		IrisImage_->ImageRenderer_->SetChangeAnimation("ScreenIris_In");
	}
	else
	{
		IrisImage_->ImageRenderer_->SetChangeAnimation("ScreenIris_Out");
	}

	IrisImage_->GetTransform()->SetWorldPosition(float4(pos.x, pos.y, static_cast<int>(ZOrder::Z00Fx00)));
}

void WorldMapScene::ScreenFadeEnd()
{
	ScreenFadeEnd_ = true;

#ifdef _DEBUG
	if (nullptr == GameEngineCore::LevelFind(NextScene_))
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 레벨");
	}
#endif // _DEBUG

	dynamic_cast <LoaddingScene*>(GameEngineCore::LevelFind("LoaddingScene"))
		->SetLoaddingNextLevel(NextScene_);

	GameEngineCore::LevelChange("LoaddingScene");

	IrisImage_->Death();

}
