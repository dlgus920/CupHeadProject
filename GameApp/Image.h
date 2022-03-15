#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImageRenderer;

class Image : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* ImageRenderer_;
public:
	Image(); // default constructer ����Ʈ ������
	~Image(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Image(const Image& _other) = delete; // default Copy constructer ����Ʈ ���������
	Image(Image&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Image& operator=(const Image& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Image& operator=(const Image&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

