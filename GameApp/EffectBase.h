#pragma once
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineActor.h>


class EffectBase : public GameEngineActor
{
private:	// member Var

public:
	EffectBase(); // default constructer ����Ʈ ������
	~EffectBase(); // default destructer ����Ʈ �Ҹ���

	EffectBase(const EffectBase& _other) = delete; // default Copy constructer ����Ʈ ���������
	EffectBase(EffectBase&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	EffectBase& operator=(const EffectBase& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EffectBase& operator=(const EffectBase&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	GameEngineImageRenderer* ImageRenderer_;


protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);

public:
	void SetImageAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop);

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

