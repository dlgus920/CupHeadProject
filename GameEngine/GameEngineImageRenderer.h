#pragma once
#include "GameEngineRenderer.h"


// 설명 :
class GameEngineTexture;
class GameEngineFolderTexture;
class GameEngineImageRenderer : public GameEngineRenderer
{
private:
	struct Animation2D
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

	// _IsForce 같은 애니메이션 인데도 바꿀거냐? true 바꾼다.
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);

	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);


protected:
	void Update(float _DeltaTime) override;

public:
	//
	inline const float4 GetTextureSize() // TODO : 잘려진 이미지 사이즈에 맞는 값을 반환하도록 해주어야 함
	{
		if (nullptr != CurTexture)
		{
			return CurTexture->GetTextureSize();
		}
		else
		{
			GameEngineDebug::MsgBoxError("텍스처가 없습니다.");
		}
	}

	inline const float4 GetCutData()
	{
		return CutData;
	}

	inline const float4 GetTextureScale() // TODO : 잘려진 이미지 사이즈에 맞는 값을 반환하도록 해주어야 함
	{
		if (nullptr != CurTexture)
		{
			return CurTexture->GetTextureScale();
		}
		else
		{
			GameEngineDebug::MsgBoxError("텍스처가 없습니다.");
		}
	}
	//

private:
	std::map<std::string, Animation2D*> AllAnimations_;
	Animation2D* CurAnimation_;

	float4 CutData;
	GameEngineTexture* CurTexture;
	void Start() override;

};

