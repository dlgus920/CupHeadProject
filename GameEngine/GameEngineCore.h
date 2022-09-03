#pragma once
#include "GameEngineLevel.h"
#include <GameEngineBase\GameEngineThreadQueue.h>

class GameEngineCore : public GameEngineObjectBase
{
	friend class GameEngineLevelControlWindow;
protected:
	GameEngineCore(); 
	~GameEngineCore(); 

private:	
	GameEngineCore(const GameEngineCore& _other) = delete;
	GameEngineCore(GameEngineCore&& _other) = delete; 
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; 
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; 

public:
	static GameEngineThreadQueue ThreadQueue;
private:
	static GameEngineLevel* NextLevel_;
	static GameEngineLevel* CurrentLevel_;
	static std::map<std::string, GameEngineLevel*> AllLevel_;

	static GameEngineCore* MainCore_;

public:
	void EngineInitialize();
	void EngineResourcesLoad();
	void EngineResourcesCreate();
	void EngineDestroy();

protected:
	virtual void Initialize() = 0;
	virtual void ResourcesLoad() = 0;
	virtual void Release() = 0;
	virtual float4 StartWindowSize() = 0;
	virtual float4 StartWindowPos() = 0;

private:
	static void WindowCreate(GameEngineCore& _RuntimeCore);
	static void Loop();
	static void MainLoop();

public:
	static GameEngineLevel* LevelFind(const std::string& _Level);
	static void LevelChange(const std::string& _Level);
	static void LevelDestroy(const std::string& _Level);

	static void SetTimeRate(float _TimeRate);

public:	

	template<typename LevelType>
	static void LevelCreate(const std::string& _Level)
	{
#ifdef _DEBUG
		if (nullptr != LevelFind(_Level))
		{
			GameEngineDebug::MsgBoxError("같은 이름의 레벨을 2번 만들려고 했습니다");
			return;
		}
#endif // _DEBUG

		AllLevel_.insert(std::make_pair(_Level, new LevelType()));
		AllLevel_[_Level]->SetName(_Level);
		AllLevel_[_Level]->Init();
		AllLevel_[_Level]->LevelStart();

		//AllLevel_[_Level]->LevelResourcesLoad();
	}

	template<typename LevelType>
	static LevelType* CurrentLevel()
	{
		//LevelType* Level = dynamic_cast<LevelType*>(CurrentLevel_);
		//return Level;	
		return dynamic_cast<LevelType*>(CurrentLevel_);
	}

	template<typename UserGameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		new int();

		UserGameType NewUserGame;

		// 윈도우 생성
		WindowCreate(NewUserGame);

		// 엔진 초기화 및 리소스 로드
		NewUserGame.EngineInitialize();
		NewUserGame.ResourcesLoad();
		NewUserGame.Initialize();

		// 메인게임 코어 셋팅
		MainCore_ = &NewUserGame;

		// Game Loop
		Loop();

		// 엔진 메모리 소멸
		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}

	static GameEngineLevel* CurrentLevel() 
	{
		return CurrentLevel_;
	}
};

