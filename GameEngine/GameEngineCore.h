#pragma once
#include "GameEngineLevel.h"

// �з� : ���� �ھ� �� ����������
// �뵵 : 
// ���� : ���� ������ �ʿ��� �⺻������ �����ϸ�, �ش� Ŭ������ ��ӹ޴� ��ü�� �ݵ�� �ʱ�ȭ/���ҽ��ε�/���ӷ���/���������� �����ϵ��� ����
//            GameEngineLevel�� �������� ���ҵ� ����
class GameEngineCore : public GameEngineObjectBase
{
	friend class GameEngineLevelControlWindow;

	// ============================================= Level ������ ���� ============================================= //
private:
	static GameEngineLevel* NextLevel_;
	static GameEngineLevel* CurrentLevel_;
	static std::map<std::string, GameEngineLevel*> AllLevel_;

public:
	template<typename LevelType>
	static void LevelCreate(const std::string& _Level)
	{
		if (nullptr != LevelFind(_Level))
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ������ 2�� ������� �߽��ϴ�");
			return;
		}

		AllLevel_.insert(std::make_pair(_Level, new LevelType()));
		AllLevel_[_Level]->Init();
		AllLevel_[_Level]->LevelStart();
	}

	static GameEngineLevel* CurrentLevel()
	{
		return CurrentLevel_;
	}

public:
	static void LevelChange(const std::string& _Level);
	static GameEngineLevel* LevelFind(const std::string& _Level);

	// ============================================== GameCore ���� ============================================== //
private:
	static GameEngineCore* MainCore_;

private:
	static void WindowCreate(GameEngineCore& _RuntimeCore);
	static void Loop();
	static void MainLoop();

public:
	template<typename UserGameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

#ifdef _DEBUG
		new int();
#endif

		UserGameType NewUserGame;

		// ������ ����
		WindowCreate(NewUserGame);

		// ���� �ʱ�ȭ �� ���ҽ� �ε�
		NewUserGame.EngineInitialize();
		NewUserGame.ResourcesLoad();
		NewUserGame.Initialize();

		// ���ΰ��� �ھ� ����
		MainCore_ = &NewUserGame;

		// Game Loop
		Loop();

		// ���� �޸� �Ҹ�
		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}

private:	// member Var

protected:
	GameEngineCore(); // default constructer ����Ʈ ������
	~GameEngineCore(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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
};




//#pragma once
//#include <GameEngineBase/GameEngineObjectBase.h>
//#include "GameEngineLevel.h"
//
//// �з� : 
//// �뵵 : 
//// ���� : 
//class GameEngineLevel;
//class GameEngineCore : public GameEngineObjectBase
//{
//private:
//	void EngineInitialize();
//	void EngineResourcesLoad();
//	void EngineResourcesCreate();
//
//	void EngineDestroy();
//
//protected:
//	GameEngineCore(); // default constructer ����Ʈ ������
//	~GameEngineCore(); // default destructer ����Ʈ �Ҹ���
//
//protected:		// delete constructer
//	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer ����Ʈ ���������
//	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
//
//private:		//delete operator
//	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator ����Ʈ ���� ������
//	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
//
//private:
//	static GameEngineCore* MainCore_;
//
//private:
//	static void WindowCreate(GameEngineCore& _RuntimeCore);
//	static void Loop();
//	static void MainLoop();
//
//public:
//	template<typename UserGameType>
//	static void Start() 
//	{
//		GameEngineDebug::LeakCheckOn();
//
//		// �ŷ��� ��.
//#ifdef _DEBUG
//		// ����׶��� ���� ������̴�.
//		new int();
//#endif
//		UserGameType NewUserGame;
//		WindowCreate(NewUserGame);
//
//		NewUserGame.EngineInitialize();
//
//		NewUserGame.ResourcesLoad();
//		NewUserGame.Initialize();
//
//		MainCore_ = &NewUserGame;
//
//		Loop();
//
//		NewUserGame.Release();
//		NewUserGame.EngineDestroy();
//
//		return;
//	}
//
//protected:
//	virtual void Initialize() = 0;
//	virtual void ResourcesLoad() = 0;
//	virtual void Release() = 0;
//
//public:
//	virtual float4 StartWindowSize() = 0;
//	virtual float4 StartWindowPos() = 0;
//
//
//
//////////////////////////////////////// Level
//
//public:
//	//template<typename LevelType>
//	//static void LevelCreate(const std::string& _Level) 
//	//{
//	//	if (nullptr != LevelFind(_Level))
//	//	{
//	//		GameEngineDebug::MsgBoxError("���� �̸��� ������ 2�� ������� �߽��ϴ�");
//	//		return;
//	//	}
//
//	//	AllLevel_.insert(std::make_pair(_Level, new LevelType()));
//	//	AllLevel_[_Level]->Init();
//	//	AllLevel_[_Level]->LevelStart();
//	//}
//
//	template<typename LevelType>
//	static LevelType* LevelCreate(const std::string& _Level)
//	{
//		if (nullptr != LevelFind(_Level))
//		{
//			GameEngineDebug::MsgBoxError("���� �̸��� ������ 2�� ������� �߽��ϴ�");
//			return nullptr;
//		}
//		LevelType* NewLevel = new LevelType();
//
//		AllLevel_.insert(std::make_pair(_Level, NewLevel));
//		AllLevel_[_Level]->Init();
//		AllLevel_[_Level]->LevelStart();
//
//		return NewLevel;
//	}
//
//
//
//	static void LevelChange(const std::string& _Level);
//	static GameEngineLevel* LevelFind(const std::string& _Level);
//
//	template<typename LevelType>
//	static LevelType* LevelFind(const std::string& _Level)
//	{
//		std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Level);
//		if (FindIter != AllLevel_.end())
//		{
//			return dynamic_cast<LevelType*> (FindIter->second);
//		}
//		return nullptr;
//	}
//
//private:
//	static GameEngineLevel* NextLevel_;
//	static GameEngineLevel* CurrentLevel_;
//	static std::map<std::string, GameEngineLevel*> AllLevel_;
//
//};
//
