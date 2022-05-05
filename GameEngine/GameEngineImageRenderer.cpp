#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTextureManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineSamplerManager.h"
#include "GameEngineCore.h"

/// ///////////////////////////////////////////////////////////////////

GameEngineImageRenderer::GameEngineImageRenderer()
	: CutData(0, 0, 1, 1)
	, CurAnimation_(nullptr)
	, CurTexture(nullptr)
	, IsPlay_(true)
{
}

GameEngineImageRenderer::~GameEngineImageRenderer()
{
	for (auto& Animation : AllAnimations_)
	{
		if (nullptr == Animation.second)
		{
			continue;
		}

		delete Animation.second;
		Animation.second = nullptr;
	}
}

GameEngineImageRenderer::GameEngineImageRenderer(const GameEngineImageRenderer& _Other)
	: CutData(0, 0, 1, 1)
	, CurAnimation_(nullptr)
	, CurTexture(nullptr)
	, IsPlay_(true)
{	
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();
	SetRenderingPipeLine("Texture");
}
void GameEngineImageRenderer::Update(float _DeltaTime)
{
	if (nullptr == CurAnimation_)
	{
		return;
	}

	CurAnimation_->Update(_DeltaTime);
}

void GameEngineImageRenderer::SetRenderingPipeLineSettingNext()
{
	ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData);

	ResultColor = float4::ONE;
	ShaderHelper.SettingConstantBufferLink("ResultColor", ResultColor); // ���� �ռ�
}
void GameEngineImageRenderer::SetIndex(const int Index)
{
#ifdef _DEBUG
	if (nullptr == CurTexture)
	{
		GameEngineDebug::MsgBoxError("�ؽ�ó�� �������� �ʴµ� �ε����� �����Ϸ��� �߽��ϴ�");
	}

	if (false == CurTexture->IsCut())
	{
		GameEngineDebug::MsgBoxError("�߸��� ���� �ؽ�ó�� �ε����� �����Ϸ��� �߽��ϴ�.");
	}
#endif // _DEBUG

	CutData = CurTexture->GetCutData(Index);

}
void GameEngineImageRenderer::SetCurAnimationFrame(int _Frame)
{
	GetCurrentAnimation()->SetCurrentIndex(_Frame);
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName, const std::string& _Sampler/* = ""*/)
{
	CurTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
#ifdef _DEBUG
	if (nullptr == CurTexture)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �����Ϸ��� �߽��ϴ�");
		return;
	}
#endif // _DEBUG

	ShaderHelper.SettingTexture("Tex", _ImageName);

	GameEngineSampler* Sampler = GameEngineSamplerManager::GetInst().Find(_Sampler);

	if (nullptr == Sampler)
	{
		return;
	}

	ShaderHelper.SettingSampler("Smp", _Sampler);
}
void GameEngineImageRenderer::CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop /*= true*/)
{
#ifdef _DEBUG
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("�̹� �����ϴ� �ִϸ��̼��� �� ��������ϴ�.");
	}
#endif // _DEBUG

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->AnimationTexture_ = GameEngineTextureManager::GetInst().Find(_TextureName);
#ifdef _DEBUG
	if (nullptr == NewAnimation->AnimationTexture_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �ִϸ��̼��� ������� �߽��ϴ�.");
	}
#endif // _DEBUG

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = nullptr;
	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}
void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _FolderTexName, const std::string& _Name, float _InterTime, bool _Loop /*= true*/)
{
	GameEngineFolderTexture* FolderTexture = GameEngineFolderTextureManager::GetInst().Find(_FolderTexName);

#ifdef _DEBUG
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("�̹� �����ϴ� �ִϸ��̼��� �� ��������ϴ�.");
	}

	if (nullptr == FolderTexture)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���� �ؽ�ó�� �����Ϸ��� �߽��ϴ�..");
	}
#endif // _DEBUG

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = FolderTexture;
	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}
void GameEngineImageRenderer::SetChangeAnimation(const std::string& _Name, bool _IsForce /*= false*/)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
#ifdef _DEBUG
	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("�ִϸ��̼��� �ִϸ��̼� nullptr �Դϴ�");
	}
#endif // _DEBUG

	if (false == _IsForce && CurAnimation_ == FindIter->second)
	{
		return;
	}

	CurAnimation_ = FindIter->second;
	if (nullptr == CurAnimation_->FolderTextures_)
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->AnimationTexture_);
	}
	else
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->FolderTextures_->GetTextureIndex(CurAnimation_->CurFrame_));
	}
	CurAnimation_->Reset();
	AnimationPlay();
}

void GameEngineImageRenderer::SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
#ifdef _DEBUG
	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("�ִϸ��̼��� �ִϸ��̼� nullptr �Դϴ�");
	}
#endif // _DEBUG

	FindIter->second->EndCallBack_.push_back(_CallBack);
}
void GameEngineImageRenderer::SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
#ifdef _DEBUG
	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("�ִϸ��̼��� �ִϸ��̼� nullptr �Դϴ�");
	}
#endif // _DEBUG

	FindIter->second->FrameCallBack_[_Index].push_back(_CallBack);
}

void GameEngineImageRenderer::SetLevelImage(const std::string& _ImageName, const std::string& _Sampler/* = ""*/)
{
	CurTexture = GameEngineTextureManager::GetInst().FindLevelRes(_ImageName);
#ifdef _DEBUG
	if (nullptr == CurTexture)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �����Ϸ��� �߽��ϴ�");
		return;
	}
#endif // _DEBUG

	ShaderHelper.SettingLevelTexture("Tex", _ImageName);

	GameEngineSampler* Sampler = GameEngineSamplerManager::GetInst().Find(_Sampler);

	if (nullptr == Sampler)
	{
		return;
	}

	ShaderHelper.SettingSampler("Smp", _Sampler);
}
void GameEngineImageRenderer::CreateLevelAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop /*= true*/)
{
#ifdef _DEBUG
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("�̹� �����ϴ� �ִϸ��̼��� �� ��������ϴ�.");
	}
#endif // _DEBUG

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->AnimationTexture_ = GameEngineTextureManager::GetInst().FindLevelRes(_TextureName);
#ifdef _DEBUG
	if (nullptr == NewAnimation->AnimationTexture_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �ִϸ��̼��� ������� �߽��ϴ�.");
	}
#endif // _DEBUG

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = nullptr;
	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}
void GameEngineImageRenderer::CreateLevelAnimationFolder(const std::string& _FolderTexName, const std::string& _Name, float _InterTime, bool _Loop /*= true*/)
{
	GameEngineFolderTexture* FolderTexture = GameEngineFolderTextureManager::GetInst().FindLevelRes(_FolderTexName);

#ifdef _DEBUG
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("�̹� �����ϴ� �ִϸ��̼��� �� ��������ϴ�.");
	}

	if (nullptr == FolderTexture)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���� �ؽ�ó�� �����Ϸ��� �߽��ϴ�..");
	}
#endif // _DEBUG

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = FolderTexture;
	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}

const bool GameEngineImageRenderer::GetCurAnimation_End()
{
#ifdef _DEBUG
	if (nullptr == CurAnimation_)
	{
		GameEngineDebug::MsgBoxError("���� ���ϸ��̼��� ����");
	}
#endif // _DEBUG


	return CurAnimation_->IsAnimationEnd();
}
const bool GameEngineImageRenderer::GetCurAnimation_End(std::string Animation_Name)
{
#ifdef _DEBUG
	if (nullptr == CurAnimation_)
	{
		GameEngineDebug::MsgBoxError("���� ���ϸ��̼��� ����");
	}
#endif // _DEBUG

	if (CurAnimation_->GetName() != Animation_Name)
	{
		return false;
	}

	return CurAnimation_->IsAnimationEnd();
}
