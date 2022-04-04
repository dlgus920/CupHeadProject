#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "GameEngine/GameEngineRenderer.h"
#include "Image.h"


Image::Image() // default constructer 디폴트 생성자
{

}

Image::~Image() // default destructer 디폴트 소멸자
{

}

void Image::Start()
{
	//ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
}

void Image::Update(float _DeltaTime)
{
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
void Image::SetImageLocalScaling(const float4& _Value)
{
	ImageRenderer_->GetTransform()->SetLocalScaling(_Value);
}

void Image::SetImageWorldScaling(const float4& _Value)
{
	ImageRenderer_->GetTransform()->SetWorldScaling(_Value);
}

void Image::SetImageLocalPosition(const float4& _Value)
{
	ImageRenderer_->GetTransform()->SetLocalPosition(_Value);
}

void Image::SetImageWorldPosition(const float4& _Value)
{
	ImageRenderer_->GetTransform()->SetWorldPosition(_Value);
}

void Image::SetReserveDeath(std::string _Name)
{
	SetImageAnimationEndFunc<Image>(_Name, &Image::Death, this);
}

void Image::SetAdjustImzgeSize()
{
	ImageRenderer_->SetAdjustImzgeSize();
}

void Image::SetAnimationFrame(int Frame)
{
	
}
