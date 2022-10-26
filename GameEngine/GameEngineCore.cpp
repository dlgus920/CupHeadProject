#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineDevice.h"
#include "GameEngineLevel.h"
#include "GameEngineInput.h"
#include "GameEngineCollision.h"
#include "GameEngineBase/GameEngineDirectory.h"
#include "GameEngineBase/GameEngineFile.h"


GameEngineThreadQueue GameEngineCore::ThreadQueue = GameEngineThreadQueue("GameEngineThread");

GameEngineCore* GameEngineCore::MainCore_ = nullptr;
float TimeRate_ =1.f;

std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel_;
GameEngineLevel* GameEngineCore::NextLevel_ = nullptr;
GameEngineLevel* GameEngineCore::CurrentLevel_ = nullptr;

GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

void GameEngineCore::EngineInitialize()
{
	GameEngineDevice::GetInst().Initialize();
	EngineResourcesLoad();
	EngineResourcesCreate();
	GameEngineDevice::GetInst().CreateSwapChain();
	// 엔진용 파이프라인

	GameEngineCollision::Init();

	GameEngineSoundManager::GetInst().Initialize();
}

void GameEngineCore::EngineDestroy()
{
	for (auto& Level : AllLevel_)
	{
		if (true)
		{
			delete  Level.second;
			Level.second = nullptr;
		}
	}

	ThreadQueue.Destroy();

	GameEngineManagerHelper::ManagerRelease();
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
	GameEngineDevice::Destroy();
	GameEngineWindow::Destroy();
}

void GameEngineCore::MainLoop()
{
	GameEngineTime::GetInst().TimeCheck();
	GameEngineSoundManager::GetInst().SoundUpdate();
	GameEngineInput::GetInst().Update();

	if (nullptr != NextLevel_)
	{
		if (nullptr == CurrentLevel_)
		{
			CurrentLevel_ = NextLevel_;
			NextLevel_->LevelChangeStartActorEvent(NextLevel_);
			NextLevel_->LevelChangeStartEvent(NextLevel_);
		}
		else
		{
			CurrentLevel_->LevelChangeEndActorEvent(NextLevel_);
			CurrentLevel_->LevelChangeEndEvent(NextLevel_);

			NextLevel_->LevelChangeStartActorEvent(CurrentLevel_);
			NextLevel_->LevelChangeStartEvent(CurrentLevel_);

			LevelDestroy(CurrentLevel_->GetName());

			CurrentLevel_ = NextLevel_;
		}

		NextLevel_ = nullptr;

		GameEngineTime::GetInst().TimeCheckReset();
	}
#ifdef _DEBUG
	if (nullptr == CurrentLevel_)
	{
		GameEngineDebug::MsgBoxError("현재 레벨이 존재하지 않습니다.");
	}
#endif // _DEBUG

	float Time = GameEngineTime::GetInst().GetDeltaTime() *TimeRate_;

	CurrentLevel_->LevelUpdate(Time);
	CurrentLevel_->ActorUpdate(Time);
	CurrentLevel_->Render(Time);
	CurrentLevel_->Release(Time);

}

void GameEngineCore::WindowCreate(GameEngineCore& _RuntimeCore)
{
	GameEngineWindow::GetInst().CreateMainWindow("MainWindow", _RuntimeCore.StartWindowSize(), _RuntimeCore.StartWindowPos());
}

void GameEngineCore::LevelDestroy(const std::string& _Level)
{
	GameEngineLevel* Level = LevelFind(_Level);
#ifdef _DEBUG
	if (nullptr == Level)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 레벨을 지우려고 했습니다.");
		return;
	}
#endif // _DEBUG

	GameEngineTextureManager::GetInst().DestroyLevelRes(Level);
	GameEngineFolderTextureManager::GetInst().DestroyLevelRes(Level);
	GameEngineSoundManager::GetInst().DestroyLevelRes(Level);

	AllLevel_.erase(AllLevel_.find(_Level));
	delete Level;
}

void GameEngineCore::Loop()
{
	GameEngineTime::GetInst().TimeCheckReset();
	GameEngineWindow::GetInst().Loop(&GameEngineCore::MainLoop);
}

GameEngineLevel* GameEngineCore::LevelFind(const std::string& _Level)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Level);
	if (FindIter != AllLevel_.end())
	{
		return FindIter->second;
	}
	return nullptr;
}

void GameEngineCore::SetTimeRate(float _TimeRate)
{
	TimeRate_ = _TimeRate;
}

void GameEngineCore::LevelChange(const std::string& _Level)
{
	GameEngineLevel* FindLevel = LevelFind(_Level);

	if (FindLevel == CurrentLevel_)
	{
		return;
	}
#ifdef _DEBUG
	if (nullptr == FindLevel)
	{
		GameEngineDebug::MsgBoxError("Next Level Is Nullptr");
	}
#endif // _DEBUG

	NextLevel_ = FindLevel;
}
