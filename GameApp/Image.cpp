#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "GameEngine/GameEngineRenderer.h"
#include "Image.h"


Image::Image() // default constructer ����Ʈ ������
{

}

Image::~Image() // default destructer ����Ʈ �Ҹ���
{

}

Image::Image(Image&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void Image::Start()
{
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	//ImageRenderer_->SetAdjustImzgeSize();
	//PlayerImageRenderer->SetImage("Animation.png");
	//PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
}

void Image::Update(float _DeltaTime)
{
}

void Image::SetImageAnimation(const std::string& _TextureName,const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	ImageRenderer_->CreateAnimation(_TextureName,_Name, _StartFrame, _EndFrame, _InterTime, _Loop);
	ImageRenderer_->SetChangeAnimation(_Name);
	SetAdjustImzgeSize();
}

void Image::SetImageAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop)
{
	ImageRenderer_->CreateAnimationFolder(_Name, _FolderTexName, _InterTime, _Loop);
	ImageRenderer_->SetChangeAnimation(_Name);
	SetAdjustImzgeSize();
}
void Image::SetImageTexture(const std::string& _TextureName)
{
	ImageRenderer_->SetImage(_TextureName);
	SetAdjustImzgeSize();

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
	SetImageAnimationEndFunc<Image>(_Name, &Image::Death, this);
}

void Image::SetAdjustImzgeSize()
{
	ImageRenderer_->SetAdjustImzgeSize();
}

void Image::SetAnimationFrame(int Frame)
{
	
}
