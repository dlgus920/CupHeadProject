#pragma once
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineActor.h>


class EffectBase : public GameEngineActor
{
private:	// member Var

public:
	EffectBase(); // default constructer 디폴트 생성자
	~EffectBase(); // default destructer 디폴트 소멸자

	EffectBase(const EffectBase& _other) = delete; // default Copy constructer 디폴트 복사생성자
	EffectBase(EffectBase&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	EffectBase& operator=(const EffectBase& _other) = delete; // default Copy operator 디폴트 대입 연산자
	EffectBase& operator=(const EffectBase&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	GameEngineImageRenderer* ImageRenderer_;


protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);

public:
	void SetImageAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop);

	void SetAnimationReserveDeath(std::string _Name);

	template <typename EffectType> // TODO: 나중ㅇ 람다식으로 즉석 함수만들어서 넣는 기능 추가하기
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

