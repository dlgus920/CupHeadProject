#include "PreCompile.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTexture.h"
#include "GameEngineLevel.h"


GameEngineTextureManager* GameEngineTextureManager::Inst = new GameEngineTextureManager();
std::mutex GameEngineTextureManager::ManagerLock;

GameEngineTextureManager::GameEngineTextureManager() // default constructer 디폴트 생성자
{

}

GameEngineTextureManager::~GameEngineTextureManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineTexture*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();

	auto iter0 = GlobalResourcesMap.begin();
	auto iter1 = GlobalResourcesMap.end();

	for (; iter0 != iter1; ++iter0)
	{
		for (const std::pair<std::string, GameEngineTexture*>& Res : iter0->second)
		{
			if (nullptr != Res.second)
			{
				delete Res.second;
			}
		}
	}
	GlobalResourcesMap.clear();
}

GameEngineTextureManager::GameEngineTextureManager(GameEngineTextureManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



GameEngineTexture* GameEngineTextureManager::Create(const std::string& _Name, ID3D11Texture2D* _Texture2D)
{
	std::string UpName = GameEngineString::toupper(_Name);

	GameEngineTexture* FindRes = Find(UpName);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(UpName + " Is Overlap Create");
	}
#endif // _DEBUG


	GameEngineTexture* NewRes = new GameEngineTexture();
	NewRes->SetName(UpName);
	NewRes->Create(_Texture2D);
	{
		std::lock_guard Lock(ManagerLock);
		ResourcesMap.insert(std::map<std::string, GameEngineTexture*>::value_type(UpName, NewRes));
	}
	return NewRes;
}

GameEngineTexture* GameEngineTextureManager::Load(const std::string& _Path)
{
	return Load(GameEngineString::toupper(GameEnginePath::GetFileName(_Path)), _Path);
}

GameEngineTexture* GameEngineTextureManager::Load(const std::string& _Name, const std::string& _Path)
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
		std::lock_guard Lock(ManagerLock);
		ResourcesMap.insert(std::map<std::string, GameEngineTexture*>::value_type(_Name, NewRes));
	}
	return NewRes;
}

GameEngineTexture* GameEngineTextureManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineTexture*>::iterator FindIter;
	{
		std::lock_guard Lock(ManagerLock);

		FindIter = ResourcesMap.find(GameEngineString::toupper(_Name));
	}

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}




GameEngineTexture* GameEngineTextureManager::LoadLevelRes(GameEngineLevel* Level, const std::string& _Path)
{
	return LoadLevelRes(Level, GameEngineString::toupper(GameEnginePath::GetFileName(_Path)), _Path);
}

GameEngineTexture* GameEngineTextureManager::LoadLevelRes(GameEngineLevel* Level, const std::string& _Name, const std::string& _Path)
{
	std::string UpName = GameEngineString::toupper(_Name);

	GameEngineTexture* FindRes = FindLevelRes(Level, UpName);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(UpName + " Is Overlap Load");
	}
#endif // _DEBUG

	GameEngineTexture* NewRes = new GameEngineTexture();
	NewRes->SetName(UpName);
	NewRes->Load(_Path);
	{
		std::lock_guard Lock(ManagerLock);

		std::map<GameEngineLevel*, std::map<std::string, GameEngineTexture*>>::iterator FindIterglobal = GlobalResourcesMap.find(Level);

		if (FindIterglobal == GlobalResourcesMap.end())
		{
			std::map<std::string, GameEngineTexture*> FindIter;

			FindIter.insert(std::make_pair(UpName, NewRes));

			GlobalResourcesMap.insert(std::make_pair(Level, FindIter));

			return NewRes;
		}

		FindIterglobal->second.insert(std::map<std::string, GameEngineTexture*>::value_type(UpName, NewRes));
	}
	return NewRes;
}

GameEngineTexture* GameEngineTextureManager::FindLevelRes(GameEngineLevel* Level, const std::string& _Name)
{
	std::string UpName = GameEngineString::toupper(_Name);

	std::map<std::string, GameEngineTexture*>::iterator FindIter;
	std::map<GameEngineLevel*, std::map<std::string, GameEngineTexture*>>::iterator FindIterglobal;

	{
		std::lock_guard Lock(ManagerLock);

		FindIterglobal = GlobalResourcesMap.find(Level);
	}

	if (FindIterglobal == GlobalResourcesMap.end())
	{
		return nullptr;
	}

	{
		std::lock_guard Lock(ManagerLock);

		FindIter = FindIterglobal->second.find(UpName);
	}

	if (FindIter != FindIterglobal->second.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

void GameEngineTextureManager::DestroyLevelRes(GameEngineLevel* _Level)
{
	std::map<GameEngineLevel*, std::map<std::string, GameEngineTexture*>>::iterator FindIterglobal = GlobalResourcesMap.find(_Level);

#ifdef _DEBUG
	//if (GlobalResourcesMap.end() == FindIterglobal)
	//{
	//	GameEngineDebug::MsgBox("존재하지 않는 레벨의 리소스를 제거함");
	//	return;
	//}

#endif // _DEBUG

	if (FindIterglobal == GlobalResourcesMap.end())
	{
		return;
	}

	for (const std::pair<std::string, GameEngineTexture*>& Res : FindIterglobal->second)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	FindIterglobal->second.clear();

	GlobalResourcesMap.erase(FindIterglobal);
}