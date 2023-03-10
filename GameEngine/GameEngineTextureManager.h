#pragma once
#include "GameEngineDevice.h"
#include <mutex>

class GameEngineTexture;
class GameEngineLevel;
class GameEngineTextureManager
{
private:
	static GameEngineTextureManager* Inst;
	static std::mutex ManagerLock;

public:
	static GameEngineTextureManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::map<std::string, GameEngineTexture*> ResourcesMap;
	
	std::map<GameEngineLevel*, std::map<std::string, GameEngineTexture*>> LocalResourcesMap; //(Level, (Name, Texture))

public:
	GameEngineTexture* Create(const std::string& _Name, ID3D11Texture2D* _Texture2D);
	GameEngineTexture* Load(const std::string& _Path);
	GameEngineTexture* Load(const std::string& _Name, const std::string& _Path);
	GameEngineTexture* Find(const std::string& _Name);



	GameEngineTexture* LoadLevelRes(const std::string& _Path);
	GameEngineTexture* LoadLevelRes(const std::string& _Name, const std::string& _Path);
	GameEngineTexture* FindLevelRes(const std::string& _Name);
	void DestroyLevelRes(GameEngineLevel* _Level);

private:
	GameEngineTextureManager(); // default constructer 디폴트 생성자
	~GameEngineTextureManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineTextureManager(const GameEngineTextureManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineTextureManager(GameEngineTextureManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineTextureManager& operator=(const GameEngineTextureManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineTextureManager& operator=(const GameEngineTextureManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
};




