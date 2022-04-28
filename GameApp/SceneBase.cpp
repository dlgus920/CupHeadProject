#include "PreCompile.h"
#include "SceneBase.h"
#include "Image.h"

#include "UserGame.h"

SceneBase::SceneBase() 
	: FadeImage_(nullptr)
	, TimeCheck_(0.f)
	, BlendRate_(1.f)
{

}

SceneBase::~SceneBase() // default destructer 디폴트 소멸자
{

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

GameEngineTexture* SceneBase::SceneTextureLoad(const std::string& _Path)
{

	return Load(GameEngineString::toupper(GameEnginePath::GetFileName(_Path)), _Path);
}

GameEngineTexture* SceneBase::SceneTextureLoad(const std::string& _Name, const std::string& _Path)
{
	GameEngineTexture* FindRes = Find(_Name);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}
#endif // _DEBUG

	GameEngineTexture* NewRes = new GameEngineTexture();
	NewRes->SetName(_Name);
	NewRes->Load(_Path);
	{
		//std::lock_guard Lock(ManagerLock);
		TextureResourcesMap.insert(std::map<std::string, GameEngineTexture*>::value_type(_Name, NewRes));
	}
	return NewRes;
}

GameEngineTexture* SceneBase::SceneTextureFind(const std::string& _Name)
{
	std::map<std::string, GameEngineTexture*>::iterator FindIter;
	{
		//std::lock_guard Lock(ManagerLock);

		FindIter = TextureResourcesMap.find(GameEngineString::toupper(_Name));
	}

	if (FindIter != TextureResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}