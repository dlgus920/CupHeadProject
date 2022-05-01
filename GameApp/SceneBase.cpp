#include "PreCompile.h"
#include "SceneBase.h"

#include "Image.h"
#include "Effect.h"
#include "Player.h"

#include "UserGame.h"

SceneBase::SceneBase() 
	: FadeImage_(nullptr)
	, TimeCheck_(0.f)
	, BlendRate_(1.f)
	, Victory_(false)
	, Player_(nullptr)
{

}

SceneBase::~SceneBase() // default destructer 디폴트 소멸자
{
	//SceneResourceClear();
}

void SceneBase::LevelResourcesLoad()
{
}

void SceneBase::LevelStart()
{
	FadeImage_ = CreateActor<Image>();
	FadeImage_->ImageSetImage("Loading_background.png");
	FadeImage_->GetTransform()->SetWorldPosition(float4(0.f, 0.0f, static_cast<int>(ZOrder::Z02Back01)));

	BlendRate_ = 1.f;

	FadeImage_->ImageRenderer_ = FadeImage_->CreateTransformComponent<GameEngineImageRenderer>();
	FadeImage_->ImageRenderer_->SetImage("title_screen_background.png");
	FadeImage_->ImageRenderer_->SetAdjustImzgeSize();
	FadeImage_->ImageRenderer_->GetTransform()->SetWorldPosition(float4(0.f, 0.f, static_cast<int>(ZOrder::Z00Fx00)));
	FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
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

//void SceneBase::TextureLoading(GameEngineDirectory Dir)
//{
//	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();
//
//	for (size_t i = 0; i < AllFile.size(); i++)
//	{
//		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
//		// Sleep(10);
//	}
//
//	--UserGame::LoadingFolder;
//
//}

//void SceneBase::SceneResourceClear()
//{
//	for (const std::pair<std::string, GameEngineTexture*>& Res : TextureResourcesMap)
//	{
//		if (nullptr != Res.second)
//		{
//			delete Res.second;
//		}
//	}
//
//	TextureResourcesMap.clear();
//
//
//	for (const std::pair<std::string, GameEngineFolderTexture*>& Res : FolderResourcesMap)
//	{
//		if (nullptr != Res.second)
//		{
//			delete Res.second;
//		}
//	}
//
//	FolderResourcesMap.clear();
//}

void SceneBase::ReadyWALLOP()
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

void SceneBase::KnockoutEnd()
{
	GameEngineCore::SetTimeRate(1.f);

	Victory_ = true;
}

//void SceneBase::PlayerResourceLoad()
//{
//	UserGame::LoadingFolder++;
//	GameEngineCore::ThreadQueue.JobPost
//	(
//		[]()
//		{
//			GameEngineDirectory TextureDir;
//			TextureDir.MoveParent(GV_GAMEFILENAME);
//			TextureDir.MoveChild("Resources");
//			TextureDir.MoveChild("Image");
//			TextureDir.MoveChild("CharactorSprite");
//			{
//				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();
//
//				for (size_t i = 0; i < AllFile.size(); i++)
//				{
//					GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureLoad(AllFile[i].GetFullPath());
//				}
//			}
//
//			GameEngineTexture* Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("Cup.png");
//
//			Texture->Cut(20, 20);
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("Cup_Dash.png");
//			Texture->Cut(8, 1);
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("PlayerDust.png");
//			Texture->Cut(20, 6);
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("DashDust.png");
//			Texture->Cut(13, 1);
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("HitEffect.png");
//			Texture->Cut(9, 3);
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("ParryEffect.png");
//			Texture->Cut(9, 1);
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("LandDust.png");
//			Texture->Cut(6, 1);
//
//			TextureDir.MoveChild("Bullet");
//
//			{
//				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();
//
//				for (size_t i = 0; i < AllFile.size(); i++)
//				{
//					GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureLoad(AllFile[i].GetFullPath());
//				}
//			}
//
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("Bullet_Default.png");
//			Texture->Cut(8, 1);
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("Bullet_Default_Birth.png");
//			Texture->Cut(4, 1);
//			Texture = GameEngineCore::CurrentLevel<SceneBase>()->LevelTextureFind("Bullet_Default_Death.png");
//			Texture->Cut(6, 1);
//
//			UserGame::LoadingFolder--;
//		}
//	);
//}

//void SceneBase::PlayerResourceLoad()
//{
//	UserGame::LoadingFolder++;
//	GameEngineCore::ThreadQueue.JobPost
//	(
//		[]()
//		{
//			GameEngineDirectory TextureDir;
//			TextureDir.MoveParent(GV_GAMEFILENAME);
//			TextureDir.MoveChild("Resources");
//			TextureDir.MoveChild("Image");
//			TextureDir.MoveChild("CharactorSprite");
//			{
//				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();
//
//				for (size_t i = 0; i < AllFile.size(); i++)
//				{
//					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
//				}
//			}
//
//			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Cup.png");
//
//			Texture->Cut(20, 20);
//			Texture = GameEngineTextureManager::GetInst().Find("Cup_Dash.png");
//			Texture->Cut(8, 1);
//			Texture = GameEngineTextureManager::GetInst().Find("PlayerDust.png");
//			Texture->Cut(20, 6);
//			Texture = GameEngineTextureManager::GetInst().Find("DashDust.png");
//			Texture->Cut(13, 1);
//			Texture = GameEngineTextureManager::GetInst().Find("HitEffect.png");
//			Texture->Cut(9, 3);
//			Texture = GameEngineTextureManager::GetInst().Find("ParryEffect.png");
//			Texture->Cut(9, 1);
//			Texture = GameEngineTextureManager::GetInst().Find("LandDust.png");
//			Texture->Cut(6, 1);
//
//			TextureDir.MoveChild("Bullet");
//
//			{
//				std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();
//
//				for (size_t i = 0; i < AllFile.size(); i++)
//				{
//					GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
//				}
//			}
//
//			Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default.png");
//			Texture->Cut(8, 1);
//			Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default_Birth.png");
//			Texture->Cut(4, 1);
//			Texture = GameEngineTextureManager::GetInst().Find("Bullet_Default_Death.png");
//			Texture->Cut(6, 1);
//
//			UserGame::LoadingFolder--;
//		}
//	);
//}

void SceneBase::Knockout()
{
	Player_->SetVictory();

	Effect* Effect_ = CreateActor<Effect>();

	GameEngineCore::SetTimeRate(0.0001f);
	Effect_->SetPlayRate(10000.f);

	GameEngineImageRenderer* _GameEngineImageRenderer = Effect_->EffectAnimationFolderActor("Knockout", "Knockout", 0.04f, false);
	_GameEngineImageRenderer->SetEndCallBack("Knockout", std::bind(&Image::Death, Effect_));
	_GameEngineImageRenderer->SetEndCallBack("Knockout", std::bind(&SceneBase::KnockoutEnd, this));

	_GameEngineImageRenderer->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });

	Effect_->GetTransform()->SetWorldPosition(float4{ 640.f, -360.f, static_cast<float>(ZOrder::Z00Fx00) });
}