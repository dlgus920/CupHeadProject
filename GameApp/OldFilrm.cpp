#include "Precompile.h"
#include "OldFilrm.h"

OldFilrm::OldFilrm()
{
}

OldFilrm::~OldFilrm()
{
}

void OldFilrm::Start()
{
	OldFilrmRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	OldFilrmRenderer_->CreateAnimationFolder("ScreenFx","ScreenFx",0.04f);
	OldFilrmRenderer_->SetChangeAnimation("ScreenFx");
	GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
}

void OldFilrm::Update(float _DeltaTime)
{
}
