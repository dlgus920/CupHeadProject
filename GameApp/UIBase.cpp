#include "PreCompile.h"
#include "UIBase.h"
#include "OldFilrm.h"
#include "Bottom_Card.h"
#include "Bottom_HP.h"


UIBase* UIBase::UIBase_;

UIBase::UIBase()
	: Bottom_Card_(nullptr)
	, Bottom_HP_(nullptr)
	, OldFilrm_(nullptr)
	, Player_(nullptr)
	, CameraComponent(nullptr)
{

}

UIBase::~UIBase() // default destructer 디폴트 소멸자
{

}

void UIBase::TurnOffBotUI()
{
	Bottom_Card_->Off();
	Bottom_HP_->Off();
}

void UIBase::TurnOnBotUI()
{
	Bottom_Card_->On();
	Bottom_HP_->On();
}

void UIBase::OldFilrmStart()
{	
	OldFilrm_ = GetLevel()->CreateActor<OldFilrm>();

	OldFilrm_->GetTransform()->AttachTransform(GetTransform());
}

void UIBase::UIStart()
{	
	Bottom_Card_ = GetLevel()->CreateActor<Bottom_Card>();
	Bottom_HP_=	GetLevel()->CreateActor<Bottom_HP>();

	Bottom_Card_->GetTransform()->AttachTransform(GetTransform());
	Bottom_HP_->GetTransform()->AttachTransform(GetTransform());

	//Bottom_Card_->GetTransform()->SetLocalPosition(float4{ 110.f,-700.f,0.f });
	Bottom_Card_->GetTransform()->SetLocalPosition(float4{ -530.f,-330.f,0.f });
	//Bottom_HP_->GetTransform()->SetLocalPosition(float4{ 50.f,-700.f,0.f });
	Bottom_HP_->GetTransform()->SetLocalPosition(float4{ -590.f,-330.f,0.f });
}

Bottom_Card* UIBase::GetBottom_Card()
{
	return Bottom_Card_;
}

Bottom_HP* UIBase::GetBottom_HP()
{
	return Bottom_HP_;
}

void UIBase::Start()
{
	UIBase_ = this;

	GetTransform()->SetWorldPosition(float4{ 0.f,0.f,-100.f });

	CameraComponent = GetLevel()->GetMainCamera();
}

void UIBase::Update(float _DeltaTime)
{
	float4 Pos = CameraComponent->GetTransform()->GetWorldPosition();
	Pos.z = static_cast<float>(ZOrder::Z00UI);

	GetTransform()->SetWorldPosition(Pos);
	OldFilrm_->GetTransform()->SetWorldMove(float4{ 0.f,0.f,-10.f });
}
