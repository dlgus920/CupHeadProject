#include "PreCompile.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"

GameEngineRenderingPipeLineManager* GameEngineRenderingPipeLineManager::Inst = new GameEngineRenderingPipeLineManager();

GameEngineRenderingPipeLineManager::GameEngineRenderingPipeLineManager() // default constructer 디폴트 생성자
{

}

GameEngineRenderingPipeLineManager::~GameEngineRenderingPipeLineManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineRenderingPipeLine*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineRenderingPipeLineManager::GameEngineRenderingPipeLineManager(GameEngineRenderingPipeLineManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



GameEngineRenderingPipeLine* GameEngineRenderingPipeLineManager::Create(const std::string& _Name)
{
	GameEngineRenderingPipeLine* FindRes = Find(_Name);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}
#endif // _DEBUG


	GameEngineRenderingPipeLine* NewRes = new GameEngineRenderingPipeLine();
	NewRes->SetName(_Name);

	// 그리고 뭘할거냐?

	ResourcesMap.insert(std::map<std::string, GameEngineRenderingPipeLine*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLineManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLineManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineRenderingPipeLine* FindRes = Find(_Name);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}
#endif // _DEBUG

	GameEngineRenderingPipeLine* NewRes = new GameEngineRenderingPipeLine();
	NewRes->SetName(_Name);


	ResourcesMap.insert(std::map<std::string, GameEngineRenderingPipeLine*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLineManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineRenderingPipeLine*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}