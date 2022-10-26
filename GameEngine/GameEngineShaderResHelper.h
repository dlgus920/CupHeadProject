#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "GameEngineRenderingSettingData.h"
#include "GameEngine/GameEngineShader.h"

class GameEngineRenderingPipeLine;
class GameEngineTexture;
class GameEngineSampler;
class GameEngineConstantBuffer;

class GameEngineShaderResHelper
{
	friend class CameraComponent;
	friend class  GameEngineRenderer;

private:
	std::map<std::string, GameEngineConstantBufferSetting*> AllConstantBufferData_;
	std::map<std::string, GameEngineTextureSetting*> AllTextureData_;
	std::map<std::string, GameEngineSamplerSetting*> AllSamplerData_;

private:
	void Clear();

public:
	void ShaderResourcesCheck(GameEngineRenderingPipeLine* _Shader);

	void ShaderResourcesCheck(GameEngineShader* _Shader);

	bool IsConstantBuffer(const std::string& _SettingName);

	void SettingTexture(const std::string& _SettingName, const std::string& _ImageName);
	void SettingLevelTexture(const std::string& _SettingName, const std::string& _ImageName);

	void SettingTexture(const std::string& _SettingName, GameEngineTexture* _Texture);

	void SettingSampler(const std::string& _SettingName, const std::string& _Name);

	void SettingSampler(const std::string& _SettingName, GameEngineSampler* _Value);

	void ReSet();
	void Setting();

	template<typename T>
	void SettingConstantBufferLink(const std::string& _SettingName, T& _Data) 
	{
		std::string UpperName = GameEngineString::toupper(_SettingName);

		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllConstantBufferData_.find(UpperName);

#ifdef _DEBUG
		if (FindIter == AllConstantBufferData_.end())
		{
			GameEngineDebug::MsgBoxError("�������� �ʴ� ������۸� �����Ϸ��� �߽��ϴ�." + UpperName);
			return;
		}
#endif // _DEBUG

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		SettingData->Mode_ = SettingMode::Link;
		SettingData->SettingDataSize_ = sizeof(_Data);
		SettingData->SettingData_ = reinterpret_cast<char*>(&_Data);
	}

	template<typename T>
	void SettingConstantBufferSet(const std::string& _SettingName, const T& _Data)
	{
		std::string UpperName = GameEngineString::toupper(_SettingName);


		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllConstantBufferData_.find(UpperName);

#ifdef _DEBUG
		if (FindIter == AllConstantBufferData_.end())
		{
			GameEngineDebug::MsgBoxError("�������� �ʴ� ������۸� �����Ϸ��� �߽��ϴ�." + UpperName);
			return;
		}
#endif // _DEBUG

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		SettingData->Mode_ = SettingMode::Set;
		SettingData->SettingDataSize_ = sizeof(_Data);

		if (nullptr == SettingData->SettingData_)
		{
			SettingData->SettingData_ = new char[sizeof(_Data)];
		}

		memcpy_s(SettingData->SettingData_, sizeof(_Data), &_Data, sizeof(_Data));
	}

public:
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();
};

