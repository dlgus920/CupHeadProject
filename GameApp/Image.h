#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImageRenderer;

class Image : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* ImageRenderer_;
public:
	Image(); // default constructer 디폴트 생성자
	~Image(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Image(const Image& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Image(Image&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Image& operator=(const Image& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Image& operator=(const Image&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);
	virtual void ReleaseEvent();

public:

	GameEngineImageRenderer* GetImageRenderer()
	{
		return ImageRenderer_;
	}

	void SetImageAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop);
	void SetImageAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop /*= true*/);
	void SetImageLocalScaling(const float4& _Value);
	void SetImageWorldPosition(const float4& _Value);
};

