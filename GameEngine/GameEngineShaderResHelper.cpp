#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineSampler.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTexture.h"

GameEngineShaderResHelper::GameEngineShaderResHelper() 
{
}

GameEngineShaderResHelper::~GameEngineShaderResHelper() 
{

	for (auto& Setting : AllTextureData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}

	for (auto& Setting : AllSamplerData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}

	for (auto& Setting : AllConstantBufferData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}
}

bool GameEngineShaderResHelper::IsConstantBuffer(const std::string& _SettingName)
{
	std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllConstantBufferData_.find(_SettingName);

	if (FindIter == AllConstantBufferData_.end())
	{
		return false;
	}

	return true;
}


void GameEngineShaderResHelper::ShaderResourcesCheck(GameEngineShader* _Shader) 
{
	// _Shader�� ������۸� ��� ����
	// �� ������۸� �� �÷��̾ ���Ͱ� ����������� ���ߴ����� 
	// GameEngineConstantBufferSetting�� ������ �˴ϴ�.

	for (auto& ConstantBuffer : _Shader->GetConstantBuffers())
	{
		GameEngineConstantBufferSetting* SettingData = new GameEngineConstantBufferSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = ConstantBuffer.second;
		SettingData->SettingIndex_ = ConstantBuffer.first;
		auto Result = AllConstantBufferData_.insert(std::make_pair(ConstantBuffer.second->GetName(), SettingData));

		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ������۰� �̹� �����մϴ�." + ConstantBuffer.second->GetName());
		}
	}

	for (auto& Sampler : _Shader->GetSamplers())
	{
		GameEngineSamplerSetting* SettingData = new GameEngineSamplerSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = Sampler.second;
		SettingData->SettingIndex_ = Sampler.first;
		auto Result = AllSamplerData_.insert(std::make_pair(Sampler.second->GetName(), SettingData));

		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ���÷��� �̹� �����մϴ�." + Sampler.second->GetName());
		}
	}

	GameEngineTexture* ErrorTexture = GameEngineTextureManager::GetInst().Find("NotSettingError.png");

	for (auto& Texture : _Shader->GetTextures())
	{
		GameEngineTextureSetting* SettingData = new GameEngineTextureSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = ErrorTexture;
		SettingData->SettingIndex_ = Texture.first;
		auto Result = AllTextureData_.insert(std::make_pair(Texture.second, SettingData));

		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("���� �̸��� �ؽ�ó�� �̹� �����մϴ�." + Texture.second);
		}
	}

}

void GameEngineShaderResHelper::Setting() 
{
	// ������ �� �����ϱ�.
	for (auto& Setting : AllConstantBufferData_)
	{
		if (Setting.second->Mode_ == SettingMode::MAX)
		{
			GameEngineDebug::MsgBoxError("������ ������۰� ���õ��� �ʾҽ��ϴ�. >>> " + Setting.first);
		}
		

		Setting.second->ChangeData();
		Setting.second->ShaderSetting();
	}

	for (auto& Setting : AllTextureData_)
	{
		Setting.second->ShaderSetting();
	}

	for (auto& Setting : AllSamplerData_)
	{
		Setting.second->ShaderSetting();
	}

}

void GameEngineShaderResHelper::ReSet()
{
	for (auto& Setting : AllConstantBufferData_)
	{
		if (Setting.second->Mode_ == SettingMode::MAX)
		{
			GameEngineDebug::MsgBoxError("������ ������۰� ���õ��� �ʾҽ��ϴ�. >>> " + Setting.first);
		}


		Setting.second->ChangeData();
		Setting.second->ShaderReSet();
	}

	for (auto& Setting : AllTextureData_)
	{
		Setting.second->ShaderReSet();
	}

	for (auto& Setting : AllSamplerData_)
	{
		Setting.second->ShaderReSet();
	}

}

void GameEngineShaderResHelper::SettingTexture(const std::string& _SettingName, const std::string& _ImageName)
{
	std::map<std::string, GameEngineTextureSetting*>::iterator FindIter = AllTextureData_.find(_SettingName);

	if (FindIter == AllTextureData_.end())
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó ���Կ� �����Ϸ��� �߽��ϴ�." + _SettingName);
		return;
	}


	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);

	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �����Ϸ��� �߽��ϴ�. >>> " + _ImageName);
		return;
	}

	FindIter->second->Res_ = FindTexture;
}


void GameEngineShaderResHelper::SettingTexture(const std::string& _SettingName, GameEngineTexture* _Texture)
{
	std::map<std::string, GameEngineTextureSetting*>::iterator FindIter = AllTextureData_.find(_SettingName);

	if (FindIter == AllTextureData_.end())
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó ���Կ� �����Ϸ��� �߽��ϴ�." + _SettingName);
		return;
	}

	if (nullptr == _Texture)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �����Ϸ��� �߽��ϴ�. >>> " + _Texture->GetName());
		return;
	}


	FindIter->second->Res_ = _Texture;

}
