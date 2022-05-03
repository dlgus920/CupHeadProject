#include "PreCompile.h"
#include "WorldMapScene.h"

#include "LoaddingScene.h"
#include "DicePaclace.h"
#include "Stage_Mr_Wheezy.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/MouseActor.h>

#include "UserGame.h"

#include "Image.h"
#include "Map.h"
#include "Object.h"
#include "StagePoint.h"
#include "WorldMapPlayer.h"


WorldMapScene::WorldMapScene() 
	: LoadState_(this)
{

}

WorldMapScene::~WorldMapScene() // default destructer 디폴트 소멸자
{
}

void WorldMapScene::LevelStart()
{
	LoadState_.CreateState("ResourcesLoad", &WorldMapScene::ResourcesLoad_Start, &WorldMapScene::ResourcesLoad_Update, &WorldMapScene::ResourcesLoad_End);
	LoadState_.CreateState("LevelLoop", &WorldMapScene::LevelLoop_Start, &WorldMapScene::LevelLoop_Update, &WorldMapScene::LevelLoop_End);
	LoadState_.CreateState("Init", nullptr, &WorldMapScene::Init_Update, nullptr);

	//LoadState_.ChangeState("Init");
}

void WorldMapScene::LevelUpdate(float _DeltaTime)
{
	LoadState_.Update(_DeltaTime);
}

void WorldMapScene::Init_Update(float _DeltaTime)
{
	LoadState_.ChangeState("ResourcesLoad");
}

void WorldMapScene::ResourcesLoad_Start()
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
			TextureDir.MoveChild("World");
			TextureDir.MoveChild("Background");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
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
			TextureDir.MoveChild("Loading");

			GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("ScreenIris"));

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
			TextureDir.MoveChild("World");
			TextureDir.MoveChild("Background");
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
			UserGame::LoadingFolder--;
		}
	);

	ResourcesLoadFadeInit();
}

void WorldMapScene::ResourcesLoad_Update(float _DeltaTime)
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
	//GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
	//GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetWorldPosition());

	//Map::ScreenFx->GetTransform()->SetWorldPosition(GetMainCameraActor()->GetTransform()->GetWorldPosition());
}

void WorldMapScene::ResourcesLoad_End()
{
}


void WorldMapScene::LevelLoop_Start()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

	{
		// 1280 720
		Map* _Map = CreateActor<Map>();
		_Map->GetCollisionMap()->SetImage("WorldMap_PixelCheckBackground.png");
		_Map->GetCollisionMap()->SetAdjustImzgeSize();
		_Map->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z04CollisonMap00) });

		Map::CurrentMap = _Map;


		Image* MapImage = CreateActor<Image>();
		MapImage->ImageSetImage("WorldMap_Background.png");
		MapImage->ImageRenderer_->SetAdjustImzgeSize();
		MapImage->GetTransform()->SetWorldPosition(float4{ 1212.f, -939.5f, static_cast<int>(ZOrder::Z02Back10) });
	}

	{
		StagePoint* WorldMapPoint = CreateActor<StagePoint>();
		WorldMapPoint->GetTransform()->SetWorldPosition(float4{ 500.f, -1000.f, static_cast<int>(ZOrder::Z01Actor02) });

		//WorldMapPoint->SetNextScene("DicePaclace");
		WorldMapPoint->SetNextScene("Stage_Mr_Wheezy");
	}

	{
		WorldMapPlayer_ = CreateActor<WorldMapPlayer>();
		WorldMapPlayer_->GetTransform()->SetWorldPosition(float4(500, -800.0f, static_cast<int>(ZOrder::Z01Actor00Player01)));
		GetMainCameraActor()->GetTransform()->SetWorldPosition(WorldMapPlayer_->GetTransform()->GetLocalPosition());
	}

	{
		//GameEngineCore::LevelCreate<DicePaclace>("DicePaclace");
		//GameEngineCore::LevelCreate<Stage_Mr_Wheezy>("Stage_Mr_Wheezy");

	}

	{
		IrisImage_ = CreateActor<Image>();
		IrisImage_->ImageRenderer_->CreateAnimationFolder("ScreenIris", "ScreenIris_In", 0.055f, false);
		IrisImage_->ImageRenderer_->CreateAnimationFolder("ScreenIris", "ScreenIris_Out", 0.055f, false);
		IrisImage_->ImageRenderer_->SetAnimationReverse("ScreenIris_Out");

		IrisImage_->ImageRenderer_->SetEndCallBack("ScreenIris_Out", std::bind(&WorldMapScene::ScreenFadeEnd, this));

		IrisImage_->GetTransform()->SetLocalScaling(float4{ 1280.f, 720.f });
		IrisImage_->GetTransform()->SetWorldPosition(float4{ 0.f,0.f,0.f,100.f });

		IrisImage_->ImageRenderer_->Off();
	}

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

	SetScreenIris(false);

	WorldMapPlayer_->Entry();
}

void WorldMapScene::LevelLoop_Update(float _DeltaTime)
{
	LevelLoadFadeUpdate(_DeltaTime);
}

void WorldMapScene::LevelLoop_End()
{
}

void WorldMapScene::LevelEnd_Start()
{
}

void WorldMapScene::LevelEnd_Update(float _DeltaTime)
{
	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ > 1.f)
	{
		BlendRate_ += _DeltaTime * 2;

		if (BlendRate_ >= 1.f)
		{
			// 씬 체인지
		}
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
	}
}

void WorldMapScene::LevelEnd_End()
{
}

void WorldMapScene::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	//릴리즈 맵
}

void WorldMapScene::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{	
	LoadState_.ChangeState("Init");

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, static_cast<int>(ZOrder::Z00Camera00)));

	//SetScreenIris(false);

	//WorldMapPlayer_->Entry();

}

void WorldMapScene::ChangeScene(std::string _Scene)
{
	NextScene_ = _Scene;
	SetScreenIris(true);
}

void WorldMapScene::SetScreenIris(bool _In)
{
	if (IrisImage_ == nullptr)
	{
		GameEngineDebug::MsgBoxError("IrisImage 생성 안됨");
	}

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

	//dynamic_cast <LoaddingScene*>(GameEngineCore::LevelFind("LoaddingScene"))
	//	->SetLoaddingNextLevel(WorldMapScene::GetName(), NextScene_);

	GameEngineCore::LevelChange(NextScene_);

	//IrisImage_->Death();

}
