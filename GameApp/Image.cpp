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

Image::~Image() // default destructer 디폴트 소멸자
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

void Image::ImageCreateAnimation(const std::string& _TextureName,const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	ImageRenderer_->CreateAnimation(_TextureName,_Name, _StartFrame, _EndFrame, _InterTime, _Loop);
	ImageRenderer_->SetChangeAnimation(_Name);
}

void Image::ImageCreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop)
{
	ImageRenderer_->CreateAnimationFolder(_Name, _FolderTexName, _InterTime, _Loop);
	ImageRenderer_->SetChangeAnimation(_Name);
}
void Image::ImageSetImage(const std::string& _TextureName)
{
	ImageRenderer_->SetImage(_TextureName);
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