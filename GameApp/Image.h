#pragma once
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineActor.h>

class GameEngineImageRenderer;

class Image : public GameEngineActor
{
public:
	Image(); 
	~Image(); 

private:		
	Image(const Image& _other) = delete;
	Image(Image&& _other) = delete;
	Image& operator=(const Image& _other) = delete; 
	Image& operator=(const Image&& _other) = delete; 

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:	// member Var
	GameEngineImageRenderer* ImageRenderer_;

public:
	void ImageSetImage(const std::string& _TextureName);
	void ImageCreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop);
	void ImageCreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop = true);

	void SetImageLocalScaling(const float4& _Value);
	void SetImageWorldScaling(const float4& _Value);

	void SetImageLocalPosition(const float4& _Value);
	void SetImageWorldPosition(const float4& _Value);

	void SetReserveDeath(std::string _Name);

	void SetAdjustImzgeSize();

	void SetAnimationFrame(int Frame);
	
public:
	GameEngineImageRenderer* GetImageRenderer()
	{
		return ImageRenderer_;
	}

	template <typename EffectType> // TODO: 나중ㅇ 람다식으로 즉석 함수만들어서 넣는 기능 추가하기
	void SetImageAnimationEndFunc(const std::string& _Name, void(EffectType::* _EndFunc)(void), EffectType* Obj)
	{
		ImageRenderer_->SetEndCallBack(_Name, std::bind(_EndFunc, Obj));
	}

	template <typename EffectType>
	void SetImageAnimationFrameFunc(const std::string& _Name, int _Index, void(EffectType::* _FrameFunc)(void), EffectType* Obj)
	{
		ImageRenderer_->SetFrameCallBack(_Name, _Index, std::bind(_FrameFunc, Obj));
	}
};

