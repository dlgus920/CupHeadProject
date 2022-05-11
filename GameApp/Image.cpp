#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "GameEngine/GameEngineRenderer.h"
#include "Image.h"


Image::Image()
	: LifeTime_(0.f)
	, TimeCheck_(0.f)
	, DeathFuction_(nullptr)
	, ImageRenderer_(nullptr)
{

}

Image::~Image() // default destructer ����Ʈ �Ҹ���
{

}

void Image::Start()
{
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
}

void Image::Update(float _DeltaTime)
{
	if (LifeTime_ != 0.f)
	{
		TimeCheck_ += _DeltaTime;
		if (LifeTime_ < TimeCheck_)
		{
			EffectDeath();
		}
	}
}

void Image::SetReserveDeath(std::string _Name)
{
	ImageRenderer_->SetEndCallBack(_Name, std::bind(& Image::Death, this));
}

void Image::SetAnimationFrame(int Frame)
{
	ImageRenderer_->GetCurrentAnimation()->SetCurrentIndex(Frame);
}

void Image::SetImageDeathFuction(std::function<void()> _CallBack)
{
	DeathFuction_ = _CallBack;
}

void Image::SetImageDeathTime(float _LifeTime)
{
	LifeTime_ = _LifeTime;
}

void Image::EffectDeath()
{
	if (nullptr != DeathFuction_)
	{
		DeathFuction_();
	}

	Death();
}

GameEngineImageRenderer* Image::CreateImageRenderer(float4 _Scale, float4 _Pos)
{
	GameEngineImageRenderer* BackRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	BackRenderer->GetTransform()->SetLocalScaling(_Scale);
	BackRenderer->GetTransform()->SetWorldPosition(_Pos);

	return BackRenderer;
}
