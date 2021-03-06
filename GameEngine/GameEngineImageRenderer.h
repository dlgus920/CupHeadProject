#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineFolderTexture.h"
#include <GameEngineBase\GameEngineObjectNameBase.h>

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

	public:
		void Reset();
		void CallEnd();
		void CallFrame();
		void Update(float _DeltaTime);

		void FrameUpdate();
		void ReverseFrameUpdate();

	public:
		void SetCurrentIndex(int _Index)
		{
			CurFrame_ = _Index;
		}

		const int GetCurrentIndex()
		{
			return CurFrame_;
		}

		const bool IsAnimationEnd()
		{
			return IsEnd;
		}

		GameEngineTexture* GetCurAnimation(int index = 0)
		{
			if(AnimationTexture_)
				return AnimationTexture_;

			if (FolderTextures_)
				return FolderTextures_->GetTextureIndex(index);

			GameEngineDebug::MsgBoxError("존재하지 않는 텍스처");
			return nullptr;
		}
	};

public:
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

	GameEngineImageRenderer(const GameEngineImageRenderer& _Other);
	GameEngineImageRenderer(GameEngineImageRenderer&& _Other) = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer& operator=(GameEngineImageRenderer&& _Other) noexcept = delete;

private:
	void Start() override;

protected:
	void SetRenderingPipeLineSettingNext() override;
	void Update(float _DeltaTime) override;

private:
	std::map<std::string, Animation2D*> AllAnimations_;

	GameEngineTexture* CurTexture;
	Animation2D* CurAnimation_;

	bool IsPlay_;

	float4 ResultColor; 
	float4 CutData;

public:

	void SetImage(const std::string& _ImageName, const std::string& _Sampler = "");
	void CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);
	void CreateAnimationFolder(const std::string& _FolderTexName, const std::string& _Name, float _InterTime, bool _Loop = true);

	void SetLevelImage(const std::string& _ImageName, const std::string& _Sampler = "");
	void CreateLevelAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);
	void CreateLevelAnimationFolder(const std::string& _FolderTexName, const std::string& _Name, float _InterTime, bool _Loop = true);

	void SetIndex(const int Index);
	void SetCurAnimationFrame(int _Frame);
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);

	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);

public:
	const bool GetCurAnimation_End();

	const bool GetCurAnimation_End(std::string Animation_Name);

	void SetResultColor(float4 _ResultColor)
	{
		ResultColor = _ResultColor;
	}

	void SetAdjustImzgeSize()
	{
		GetTransform()->SetLocalScaling(GetImageSize());
	}

	void SetAnimationReverse(std::string _animation)
	{
		Animation2D* ani = AllAnimations_.find(_animation)->second;

		int framestart = ani->StartFrame_;
		int frameend = ani->EndFrame_;

		ani->StartFrame_ = frameend;
		ani->EndFrame_ = framestart;
		ani->CurFrame_ = frameend;
	}

	float4 GetImageSize()
	{
		if (nullptr != CurAnimation_)
		{
			//GetTransform()->SetWorldScaling(CurAnimation_->GetCurAnimation()->GetMetaDataImageSize());

			if (nullptr != CurAnimation_->AnimationTexture_)
			{
				float4 Size = CurAnimation_->GetCurAnimation()->GetCutData(0);
				float4 MetaSize = CurAnimation_->GetCurAnimation()->GetMetaDataImageSize();

				MetaSize.x *= Size.z;
				MetaSize.y *= Size.w;

				return MetaSize;
			}

			if (nullptr != CurAnimation_->FolderTextures_)
			{
				return CurAnimation_->GetCurAnimation()->GetMetaDataImageSize();
			}
		}

		if (nullptr != CurTexture)
		{
			return CurTexture->GetMetaDataImageSize();
		}
#ifdef _DEBUG
		else
		{
			GameEngineDebug::MsgBoxError("이미지가 지정되지 않았습니다.");
		}
#endif // _DEBUG


		return float4::ZERO;
	}

	inline GameEngineTexture* GetCurrentTexture()
	{
		return CurTexture;
	}

	inline GameEngineTexture* GetCurrentAnimationTexture(int index = 0)
	{
		return CurAnimation_->GetCurAnimation(index);
	}

	inline Animation2D* GetCurrentAnimation()
	{
		return CurAnimation_;
	}

	inline std::string GetCurrentAnimationName()
	{
		return CurAnimation_->GetName();
	}

	inline void IsCurrentAnimationIndex(const int _Index)
	{
		CurAnimation_->SetCurrentIndex(_Index);
	}

	inline bool IsCurrentAnimationString(const std::string& _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline bool IsCurrentAnimationPtr(const char* _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline void AnimationStop()
	{
		IsPlay_ = false;
	}

	inline void AnimationPlay()
	{
		IsPlay_ = true;
	}

};

