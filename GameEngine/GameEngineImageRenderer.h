#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineFolderTexture.h"
#include <GameEngineBase\GameEngineObjectNameBase.h>


// ���� :
class GameEngineTexture;
class GameEngineFolderTexture;
class GameEngineImageRenderer : public GameEngineRenderer
{
private:
	struct Animation2D : public GameEngineObjectNameBase
	{
		GameEngineFolderTexture* FolderTextures_;
		GameEngineTexture* AnimationTexture_;
		float InterTime_;
		float CurTime_;

		bool IsEnd;
		bool Loop_;
		int CurFrame_;
		int StartFrame_;
		int EndFrame_;

		GameEngineImageRenderer* Renderer;

		std::map<int, std::vector<std::function<void()>>> FrameCallBack_;
		std::vector<std::function<void()>> EndCallBack_;
		std::vector<std::function<void()>> StartCallBack_;

	public:
		void Reset();
		void CallStart();
		void CallEnd();
		void CallFrame();
		void Update(float _DeltaTime);

	public:
		GameEngineTexture* GetCurAnimation(int index = 0)
		{
			if(AnimationTexture_)
				return AnimationTexture_;

			if (FolderTextures_)
				return FolderTextures_->GetTextureIndex(index);

			GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó");
		}
	};

public:
	// constrcuter destructer
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

	// delete Function
	GameEngineImageRenderer(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer(GameEngineImageRenderer&& _Other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer& operator=(GameEngineImageRenderer&& _Other) noexcept = delete;

	void SetImage(const std::string& _ImageName);

	void SetIndex(const int Index);

	void CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);

	void CreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop = true);

	// _IsForce ���� �ִϸ��̼� �ε��� �ٲܰų�? true �ٲ۴�.
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);

	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);


	inline GameEngineTexture* GetCurrentTexture()
	{
		return CurTexture;
	}

	inline GameEngineTexture* GetCurrentAnimationTexture(int index = 0)
	{
		return CurAnimation_->GetCurAnimation(index);
	}

	inline std::string GetCurrentAnimationName()
	{
		return CurAnimation_->GetName();
	}

	inline bool IsCurrentAnimationString(const std::string& _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline bool IsCurrentAnimationPtr(const char* _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

protected:
	void ImageRendererStart();
	void Update(float _DeltaTime) override;

private:
	std::map<std::string, Animation2D*> AllAnimations_;
	Animation2D* CurAnimation_;

	float4 CutData;
	GameEngineTexture* CurTexture;
	void Start() override;

};

