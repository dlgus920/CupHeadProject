#pragma once
#include <GameEngine/GameEngineImageRenderer.h>
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
	void Start() override;
	void Update(float _DeltaTime) override;

public:

	GameEngineImageRenderer* GetImageRenderer()
	{
		return ImageRenderer_;
	}

	void SetImageAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop);
	void SetImageAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop /*= true*/);

	void SetImageLocalScaling(const float4& _Value);
	void SetImageWorldPosition(const float4& _Value);

	void SetAnimationReserveDeath(std::string _Name);

	template <typename EffectType> // TODO: ���ߤ� ���ٽ����� �Ｎ �Լ����� �ִ� ��� �߰��ϱ�
	void SetImageAnimationEndFunc(const std::string& _Name, void(EffectType::* _EndFunc)(void))
	{
		ImageRenderer_->SetEndCallBack(_Name, std::bind(_EndFunc, this));
	}

	template <typename EffectType>
	void SetImageAnimationFrameFunc(const std::string& _Name, int _Index, void(EffectType::* _FrameFunc)(void))
	{
		ImageRenderer_->SetFrameCallBack(_Name, _Index, std::bind(_FrameFunc, this));
	}
};

