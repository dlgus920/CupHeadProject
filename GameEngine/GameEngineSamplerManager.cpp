#include "PreCompile.h"
#include "GameEngineSamplerManager.h"
#include "GameEngineSampler.h"

GameEngineSamplerManager* GameEngineSamplerManager::Inst = new GameEngineSamplerManager();

GameEngineSamplerManager::GameEngineSamplerManager() // default constructer ����Ʈ ������
{

}

GameEngineSamplerManager::~GameEngineSamplerManager() // default destructer ����Ʈ �Ҹ���
{
	for (const std::pair<std::string, GameEngineSampler*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineSamplerManager::GameEngineSamplerManager(GameEngineSamplerManager&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



GameEngineSampler* GameEngineSamplerManager::Create(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info)
{
	GameEngineSampler* FindRes = Find(_Name);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}
#endif // _DEBUG


	GameEngineSampler* NewRes = new GameEngineSampler();
	NewRes->SetName(_Name);
	NewRes->Create(_Info);

	// �׸��� ���Ұų�?

	ResourcesMap.insert(std::map<std::string, GameEngineSampler*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineSampler* GameEngineSamplerManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineSampler*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

GameEngineSampler* GameEngineSamplerManager::CreateAndFind(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info)
{
	GameEngineSampler* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		return FindRes;
	}

	GameEngineSampler* NewRes = new GameEngineSampler();
	NewRes->SetName(_Name);
	NewRes->Create(_Info);

	ResourcesMap.insert(std::map<std::string, GameEngineSampler*>::value_type(_Name, NewRes));

	return NewRes;
}