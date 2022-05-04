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

//GameEngineImageRenderer* Effect::EffectAnimationActor(std::string _TextureName, std::string _AnimationName, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
//{
//	GameEngineImageRenderer* ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
//
//	ImageRenderer->CreateAnimation(_TextureName, _AnimationName, _StartFrame, _EndFrame, _InterTime, _Loop);
//	ImageRenderer->SetChangeAnimation(_AnimationName);
//	ImageRenderer->SetAdjustImzgeSize();
//
//	ImageRenderer->SetEndCallBack(_AnimationName, std::bind(&Effect::Death, this));
//
//	return ImageRenderer;
//}
//
//GameEngineImageRenderer* Effect::EffectAnimationFolderActor(std::string _TextureName, std::string _AnimationName, float _InterTime, bool _Loop)
//{
//	GameEngineImageRenderer* ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
//
//	ImageRenderer->CreateAnimationFolder(_TextureName, _AnimationName, _InterTime, _Loop);
//	ImageRenderer->SetChangeAnimation(_AnimationName);
//	ImageRenderer->SetAdjustImzgeSize();
//
//	ImageRenderer->SetEndCallBack(_AnimationName, std::bind(&Effect::Death, this));
//
//	return ImageRenderer;
//}

GameEngineImageRenderer* Effect::EffectAnimationActor(std::string _TextureName, std::string _AnimationName, float4 _Scale, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	GameEngineImageRenderer* ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();

	ImageRenderer->GetTransform()->SetLocalScaling(_Scale);
	ImageRenderer->CreateAnimation(_TextureName, _AnimationName, _StartFrame, _EndFrame, _InterTime, _Loop);
	ImageRenderer->SetChangeAnimation(_AnimationName);

	ImageRenderer->SetEndCallBack(_AnimationName, std::bind(&Effect::Death, this));

	return ImageRenderer;
}

GameEngineImageRenderer* Effect::EffectAnimationFolderActor(std::string _TextureName, std::string _AnimationName, float4 _Scale, float _InterTime, bool _Loop)
{
	GameEngineImageRenderer* ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();

	ImageRenderer->GetTransform()->SetLocalScaling(_Scale);
	ImageRenderer->CreateAnimationFolder(_TextureName, _AnimationName, _InterTime, _Loop);
	ImageRenderer->SetChangeAnimation(_AnimationName);

	ImageRenderer->SetEndCallBack(_AnimationName, std::bind(&Effect::Death, this));

	return ImageRenderer;
}


