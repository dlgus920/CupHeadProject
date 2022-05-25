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
	GetTransform()->SetWorldPosition(float4{ 0.f,0.f,static_cast<float>(ZOrder::Z00Camera00) });

	OldFilrm_ = GetLevel()->CreateActor<OldFilrm>();
	Bottom_Card_ = GetLevel()->CreateActor<Bottom_Card>();
	Bottom_HP_=	GetLevel()->CreateActor<Bottom_HP>();

	Bottom_Card_->GetTransform()->SetWorldPosition(float4{ 110.f,-700.f,static_cast<float>(ZOrder::Z00UI) });
	Bottom_HP_->GetTransform()->SetWorldPosition(float4{ 50.f,-700.f,static_cast<float>(ZOrder::Z00UI) });

	Camera_ = GetLevel()->GetMainCameraActor();
}

void UIBase::Update(float _DeltaTime)
{

}
