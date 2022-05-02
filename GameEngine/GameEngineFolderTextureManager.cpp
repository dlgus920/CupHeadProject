#include "PreCompile.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"

#include "GameEngineLevel.h"

GameEngineFolderTextureManager* GameEngineFolderTextureManager::Inst = new GameEngineFolderTextureManager();

GameEngineFolderTextureManager::GameEngineFolderTextureManager() // default constructer 디폴트 생성자
{

}

GameEngineFolderTextureManager::~GameEngineFolderTextureManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineFolderTexture*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineFolderTextureManager::GameEngineFolderTextureManager(GameEngineFolderTextureManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

GameEngineFolderTexture* GameEngineFolderTextureManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineFolderTexture* GameEngineFolderTextureManager::Load(const std::string& _Name, const std::string& _Path)
{
	std::string UpName = GameEngineString::toupper(_Name);

	GameEngineFolderTexture* FindRes = Find(UpName);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineFolderTexture* NewRes = new GameEngineFolderTexture();
	NewRes->SetName(UpName);
	NewRes->Load(_Path);
	ResourcesMap.insert(std::map<std::string, GameEngineFolderTexture*>::value_type(UpName, NewRes));
	return NewRes;
}

GameEngineFolderTexture* GameEngineFolderTextureManager::Find(const std::string& _Name)
{
	std::string UpName = GameEngineString::toupper(_Name);

	std::map<std::string, GameEngineFolderTexture*>::iterator FindIter = ResourcesMap.find(UpName);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

GameEngineFolderTexture* GameEngineFolderTextureManager::LoadLevelRes(GameEngineLevel* Level, const std::string& _Path)
{
	return LoadLevelRes(Level, GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineFolderTexture* GameEngineFolderTextureManager::LoadLevelRes(GameEngineLevel* Level, const std::string& _Name, const std::string& _Path)
{
	std::string UpName = GameEngineString::toupper(_Name);

	GameEngineFolderTexture* FindRes = FindLevelRes(Level, UpName);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}
#endif // _DEBUG

	GameEngineFolderTexture* NewRes = new GameEngineFolderTexture();
	NewRes->SetName(UpName);
	NewRes->Load(_Path);
	{
		std::map<GameEngineLevel*, std::map<std::string, GameEngineFolderTexture*>>::iterator FindIterglobal = GlobalResourcesMap.find(Level);

		if (FindIterglobal == GlobalResourcesMap.end())
		{
			std::map<std::string, GameEngineFolderTexture*> ddd;

			ddd.insert(std::map<std::string, GameEngineFolderTexture*>::value_type(UpName, NewRes));

			GlobalResourcesMap.insert(std::make_pair(Level, ddd));

			return NewRes;
		}
			FindIterglobal->second.insert(std::map<std::string, GameEngineFolderTexture*>::value_type(UpName, NewRes));
	}
	return NewRes;
}

GameEngineFolderTexture* GameEngineFolderTextureManager::FindLevelRes(GameEngineLevel* Level, const std::string& _Name)
{
	std::map<std::string, GameEngineFolderTexture*>::iterator FindIter;
	std::map<GameEngineLevel*, std::map<std::string, GameEngineFolderTexture*>>::iterator FindIterglobal;

	{
		FindIterglobal = GlobalResourcesMap.find(Level);
	}

	if (FindIterglobal == GlobalResourcesMap.end())
	{
		return nullptr;
	}

	{
		FindIter = FindIterglobal->second.find(GameEngineString::toupper(_Name));
	}

	if (FindIter != FindIterglobal->second.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

void GameEngineFolderTextureManager::DestroyLevelRes(GameEngineLevel* _Level)
{
}
