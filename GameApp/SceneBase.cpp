#include "PreCompile.h"
#include "SceneBase.h"

#include "Image.h"
#include "Effect.h"
#include "Player.h"

#include "UserGame.h"

#include <GameEngineBase/GameEngineFSM.h>
#include <GameEngineBase/GameEngineDirectory.h>

SceneBase::SceneBase() 
	: FadeImage_(nullptr)
	, TimeCheck_(0.f)
	, BlendRate_(1.f)
	, Victory_(false)
	, LoadingComplete_(false)
	, LoadingFadeComplete_(false)
	, Player_(nullptr)
{

}

SceneBase::~SceneBase() // default destructer ����Ʈ �Ҹ���
{
	//SceneResourceClear();
}

void SceneBase::LevelStart()
{
}

void SceneBase::LevelUpdate(float _DeltaTime)
{
}

void SceneBase::LevelChangeEndEvent()
{
}

void SceneBase::LevelChangeStartEvent()
{
}

void SceneBase::ReadyWALLOP()
{
	Image* Back = CreateActor<Image>();
	Back->ImageRenderer_->SetImage("Loading_background.png");
	Back->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Fx01)));
	Back->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
	Back->ImageRenderer_->SetResultColor(float4{ 1.f,1.f,1.f,0.3f });

	Effect* Effect_ = CreateActor<Effect>();
	GameEngineImageRenderer* _GameEngineImageRenderer = Effect_->EffectAnimationFolderActor("ReadyWALLOP!", "ReadyWALLOP!", float4{ 1280.f,720.f,1.f },0.04f, false);

	_GameEngineImageRenderer->SetEndCallBack("ReadyWALLOP!", std::bind(&Image::Death, Back));

	Effect_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
}

void SceneBase::KnockoutEnd()
{
	GameEngineCore::SetTimeRate(1.f);

	Victory_ = true;
}

void SceneBase::PlayerResourceLoad()
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
			TextureDir.MoveChild("UI");

			std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

			for (size_t i = 0; i < AllFile.size(); i++)
			{
				GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
			}
			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("Bottom_HP.png");
			Texture->Cut(6, 2);

			Texture = GameEngineTextureManager::GetInst().FindLevelRes("BottomCard_Dia.png");
			Texture->Cut(6, 1);

			Texture = GameEngineTextureManager::GetInst().FindLevelRes("BottomCard_Spade.png");
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
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}
			}

			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("Cup.png");

			Texture->Cut(20, 20);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Cup_Dash.png");
			Texture->Cut(8, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("PlayerDust.png");
			Texture->Cut(20, 6);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("DashDust.png");
			Texture->Cut(13, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("HitEffect.png");
			Texture->Cut(9, 3);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("ParryEffect.png");
			Texture->Cut(9, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("LandDust.png");
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
			TextureDir.MoveChild("Bullet");

			{
				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

				for (size_t i = 0; i < AllFile.size(); i++)
				{
					GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[i].GetFullPath());
				}
			}
			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().FindLevelRes("Bullet_Default.png");
			Texture->Cut(8, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Bullet_Default_Birth.png");
			Texture->Cut(4, 1);
			Texture = GameEngineTextureManager::GetInst().FindLevelRes("Bullet_Default_Death.png");
			Texture->Cut(6, 1);

			UserGame::LoadingFolder--;
		}
	);
}

void SceneBase::SceneResourceLoad()
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

			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("Knockout"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("ReadyWALLOP!"));
			GameEngineFolderTextureManager::GetInst().LoadLevelRes(TextureDir.PathToPlusFileName("YouDied"));

			UserGame::LoadingFolder--;
		}
	);
}

void SceneBase::ResourcesLoadFadeInit()
{
	{
		BlendRate_ = 1.f;

		FadeImage_ = CreateActor<Image>();

		FadeImage_->ImageRenderer_->SetImage("Loading_background.png");
		FadeImage_->GetTransform()->SetWorldPosition(float4{ 0.f, 0.f, static_cast<float>(ZOrder::Z00Fx00) });
		FadeImage_->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f });
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });

		HourGlass_ = CreateActor<Image>();
		HourGlass_->GetTransform()->SetWorldPosition(float4(450.f, -180.0f, static_cast<int>(ZOrder::Z01Actor02)));
		HourGlass_->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 200.f,320.f });
		HourGlass_->ImageRenderer_->CreateAnimation("HourGlass.png", "HourGlass", 0, 45, 0.05f, true);
		HourGlass_->ImageRenderer_->SetChangeAnimation("HourGlass");
		HourGlass_->CreateImageRenderer(float4{ 1280.f,720.f }, float4{ 0.f, 0.f, static_cast<float>(ZOrder::Z02Back10) })
			->SetImage("Loading_background.png");
	}

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, static_cast<float>(ZOrder::Z00Camera00)));

}

void SceneBase::LevelLoadFadeUpdate(float _DeltaTime)
{
	if (false == LoadingFadeComplete_)
	{
		BlendRate_ -= _DeltaTime * 2;

		if (BlendRate_ <= 0.f)
		{
			BlendRate_ = 0.f;
			LoadingFadeComplete_ = true;
			//FadeImage_->Death();
		}
		FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
	}
}

void SceneBase::Knockout()
{
	Player_->SetVictory();

	Effect* Effect_ = CreateActor<Effect>();

	GameEngineCore::SetTimeRate(0.0001f);
	Effect_->SetPlayRate(10000.f);

	GameEngineImageRenderer* _GameEngineImageRenderer = Effect_->EffectAnimationFolderActor("Knockout", "Knockout", float4{ 1280.f,720.f,1.f },0.04f, false);
	_GameEngineImageRenderer->SetEndCallBack("Knockout", std::bind(&Image::Death, Effect_));
	_GameEngineImageRenderer->SetEndCallBack("Knockout", std::bind(&SceneBase::KnockoutEnd, this));

	Effect_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
}