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

Image::Image(Image&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void Image::Start()
{
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	//PlayerImageRenderer->SetImage("Animation.png");
	//PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
}

void Image::Update(float _DeltaTime)
{
}

void Image::SetImageAnimation(const std::string& _TextureName,const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	ImageRenderer_->CreateAnimation(_TextureName,_Name, _StartFrame, _EndFrame, _Loop);
}

void Image::SetImageAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop)
{
	ImageRenderer_->CreateAnimationFolder(_Name, _FolderTexName, _InterTime, _Loop);
}
void Image::SetImageLocalScaling(const float4& _Value)
{
	ImageRenderer_->GetTransform()->SetLocalScaling(_Value);
}

void Image::SetImageWorldPosition(const float4& _Value)
{
	ImageRenderer_->GetTransform()->SetLocalPosition(_Value);
}

void Image::SetAnimationReserveDeath(std::string _Name)
{
	SetImageAnimationEndFunc(_Name, &Image::Death);
}
