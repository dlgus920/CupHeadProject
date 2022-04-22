#include "PreCompile.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineVertexShader.h"
#include "GameEngineBase/GameEngineFile.h"

GameEngineVertexShaderManager* GameEngineVertexShaderManager::Inst = new GameEngineVertexShaderManager();

GameEngineVertexShaderManager::GameEngineVertexShaderManager() // default constructer 디폴트 생성자
{

}

GameEngineVertexShaderManager::~GameEngineVertexShaderManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineVertexShader*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineVertexShaderManager::GameEngineVertexShaderManager(GameEngineVertexShaderManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}


GameEngineVertexShader* GameEngineVertexShaderManager::Load(const std::string& _Path, const std::string& _EntryPoint,
	UINT _VersionHigh, /*= 5*/
	UINT _VersionLow /*= 0*/
	) 
{

	std::string FileName = GameEnginePath::GetFileName(_Path);

	return Load(FileName, _Path, _EntryPoint);
}

GameEngineVertexShader* GameEngineVertexShaderManager::Load(const std::string& _Name, const std::string& _Path, const std::string& _EntryPoint,
	UINT _VersionHigh, /*= 5*/
	UINT _VersionLow /*= 0*/
	)
{
	GameEngineVertexShader* FindRes = Find(_Name);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}
#endif // _DEBUG

	GameEngineVertexShader* NewRes = new GameEngineVertexShader();
	NewRes->SetName(_Name);
	if (false == NewRes->Load(_Path, _EntryPoint, _VersionHigh, _VersionLow))
	{
		delete NewRes;
		return nullptr;
	}

	ResourcesMap.insert(std::map<std::string, GameEngineVertexShader*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineVertexShader* GameEngineVertexShaderManager::Create(
	const std::string& _Name,
	const std::string& _ShaderCode,
	const std::string& _EntryPoint,
	UINT _VersionHigh,
	UINT _VersionLow
	)
{
	GameEngineVertexShader* FindRes = Find(_Name);
#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}
#endif // _DEBUG

	GameEngineVertexShader* NewRes = new GameEngineVertexShader();
	NewRes->SetName(_Name);
	if (false == NewRes->Create(_ShaderCode, _EntryPoint, _VersionHigh, _VersionLow))
	{
		delete NewRes;
		return nullptr;
	}

	ResourcesMap.insert(std::map<std::string, GameEngineVertexShader*>::value_type(_Name, NewRes));
	return NewRes;
}


GameEngineVertexShader* GameEngineVertexShaderManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineVertexShader*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}