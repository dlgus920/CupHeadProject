#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>

#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect() 
{
}

void Effect::Start()
{
}

void Effect::Update(float _DeltaTime)
{

}

GameEngineImageRenderer* Effect::EffectAnimationActor(std::string _TextureName, std::string _AnimationName, float4 _Scale, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();

	ImageRenderer_->GetTransform()->SetLocalScaling(_Scale);
	ImageRenderer_->CreateLevelAnimation(_TextureName, _AnimationName, _StartFrame, _EndFrame, _InterTime, _Loop);
	ImageRenderer_->SetChangeAnimation(_AnimationName);

	ImageRenderer_->SetEndCallBack(_AnimationName, std::bind(&Effect::Death, this));

	return ImageRenderer_;
}

GameEngineImageRenderer* Effect::EffectAnimationFolderActor(std::string _TextureName, std::string _AnimationName, float4 _Scale, float _InterTime, bool _Loop)
{
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();

	ImageRenderer_->GetTransform()->SetLocalScaling(_Scale);
	ImageRenderer_->CreateLevelAnimationFolder(_TextureName, _AnimationName, _InterTime, _Loop);
	ImageRenderer_->SetChangeAnimation(_AnimationName);

	ImageRenderer_->SetEndCallBack(_AnimationName, std::bind(&Effect::Death, this));

	return ImageRenderer_;
}

GameEngineImageRenderer* Effect::EffectAddAnimationActor(std::string _TextureName, std::string _AnimationName, float4 _Scale, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	GameEngineImageRenderer* ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();

	ImageRenderer->GetTransform()->SetLocalScaling(_Scale);
	ImageRenderer->CreateLevelAnimation(_TextureName, _AnimationName, _StartFrame, _EndFrame, _InterTime, _Loop);
	ImageRenderer->SetChangeAnimation(_AnimationName);

	ImageRenderer->SetEndCallBack(_AnimationName, std::bind(&Effect::Death, this));

	return ImageRenderer;
}

GameEngineImageRenderer* Effect::EffectAddAnimationFolderActor(std::string _TextureName, std::string _AnimationName, float4 _Scale, float _InterTime, bool _Loop)
{
	GameEngineImageRenderer* ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();

	ImageRenderer->GetTransform()->SetLocalScaling(_Scale);
	ImageRenderer->CreateLevelAnimationFolder(_TextureName, _AnimationName, _InterTime, _Loop);
	ImageRenderer->SetChangeAnimation(_AnimationName);

	ImageRenderer->SetEndCallBack(_AnimationName, std::bind(&Effect::Death, this));

	return ImageRenderer;
}


