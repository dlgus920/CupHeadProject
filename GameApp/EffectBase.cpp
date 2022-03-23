#include "PreCompile.h"
#include "EffectBase.h"

EffectBase::EffectBase() :
	ImageRenderer_(nullptr)
{
}

EffectBase::~EffectBase() // default destructer ����Ʈ �Ҹ���
{
}

void EffectBase::Start()
{
}

void EffectBase::Update(float _DeltaTime)
{
}

void EffectBase::SetImageAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	ImageRenderer_->CreateAnimation(_TextureName, _Name, _StartFrame, _EndFrame, _InterTime, _Loop);
}

void EffectBase::SetAnimationReserveDeath(std::string _Name)
{
	SetImageAnimationEndFunc(_Name, &EffectBase::Death);
}
