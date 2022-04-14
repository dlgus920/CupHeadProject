#include "PreCompile.h"
#include "Effect.h"

Effect::Effect() 
	: ImageRenderer_(nullptr)
{
}

Effect::~Effect() // default destructer 디폴트 소멸자
{
}

void Effect::Start()
{
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
}

void Effect::Update(float _DeltaTime)
{
}

void Effect::SetDust()
{
	GameEngineImageRenderer* ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	ImageRenderer->CreateAnimation("Dust.png", "Dust", 57, 58, 0.05f);
	ImageRenderer->SetEndCallBack("Dust", std::bind(&Effect::Death, this));
	ImageRenderer->SetChangeAnimation("Dust");
	GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetMetaDataImageSize());
}

