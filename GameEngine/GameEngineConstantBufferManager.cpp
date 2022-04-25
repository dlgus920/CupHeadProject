#include "PreCompile.h"
#include "GameEngineConstantBufferManager.h"
#include "GameEngineConstantBuffer.h"

GameEngineConstantBufferManager* GameEngineConstantBufferManager::Inst = new GameEngineConstantBufferManager();

GameEngineConstantBufferManager::GameEngineConstantBufferManager() // default constructer 디폴트 생성자
{

}

GameEngineConstantBufferManager::~GameEngineConstantBufferManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineConstantBuffer*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineConstantBufferManager::GameEngineConstantBufferManager(GameEngineConstantBufferManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



GameEngineConstantBuffer* GameEngineConstantBufferManager::Create(const std::string& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc, ID3D11ShaderReflectionConstantBuffer* _VarInfo)
{
	std::string UpperName = GameEngineString::toupper(_Name);

	GameEngineConstantBuffer* FindRes = Find(UpperName);

#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}
#endif // _DEBUG


	GameEngineConstantBuffer* NewRes = new GameEngineConstantBuffer();
	NewRes->SetName(UpperName);
	NewRes->Create(_BufferDesc, _VarInfo);

	// 그리고 뭘할거냐?

	ResourcesMap.insert(std::map<std::string, GameEngineConstantBuffer*>::value_type(UpperName, NewRes));
	return NewRes;
}

GameEngineConstantBuffer* GameEngineConstantBufferManager::CreateAndFind(const std::string& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc, ID3D11ShaderReflectionConstantBuffer* _VarInfo)
{
	std::string UpperName = GameEngineString::toupper(_Name);

	GameEngineConstantBuffer* FindRes = Find(UpperName);

	if (nullptr != FindRes)
	{
		return FindRes;
	}


	GameEngineConstantBuffer* NewRes = new GameEngineConstantBuffer();
	NewRes->SetName(UpperName);
	NewRes->Create(_BufferDesc, _VarInfo);

	ResourcesMap.insert(std::map<std::string, GameEngineConstantBuffer*>::value_type(UpperName, NewRes));

	return NewRes;
}

GameEngineConstantBuffer* GameEngineConstantBufferManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineConstantBuffer* GameEngineConstantBufferManager::Load(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::toupper(_Name);

	GameEngineConstantBuffer* FindRes = Find(UpperName);

#ifdef _DEBUG
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}
#endif // _DEBUG

	GameEngineConstantBuffer* NewRes = new GameEngineConstantBuffer();
	NewRes->SetName(UpperName);

	ResourcesMap.insert(std::map<std::string, GameEngineConstantBuffer*>::value_type(UpperName, NewRes));
	return NewRes;
}

GameEngineConstantBuffer* GameEngineConstantBufferManager::Find(const std::string& _Name)
{
	std::string UpperName = GameEngineString::toupper(_Name);

	std::map<std::string, GameEngineConstantBuffer*>::iterator FindIter = ResourcesMap.find(UpperName);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}