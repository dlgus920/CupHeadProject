#include "PreCompile.h"
#include "Bottom_Card.h"

Bottom_Card::Bottom_Card()
	: CurCount_(0)
	, WaitingCount_(0)
	, RiseingIndex_(0)
	, CardPos_{}
	, UICard_{}
	, WorkEnd_(false)
{

}

Bottom_Card::~Bottom_Card() // default destructer 디폴트 소멸자
{

}

void Bottom_Card::Start()
{	
	CutData_ = { 20.f,17.f,0.f };


	for (int i = 0; i < 6; ++i)
	{
		UICard_[i] = CreateTransformComponent<GameEngineImageRenderer>();
		UICard_[i]->CreateLevelAnimation("BottomCard_Dia.png", "BottomCard_Dia", 0, 5, 0.1f);
		UICard_[i]->CreateLevelAnimation("BottomCard_Spade.png", "BottomCard_Spade", 0, 5, 0.1f);
		UICard_[i]->GetTransform()->SetLocalPosition(float4{25.f * i,0.f,0.f});
		UICard_[i]->GetTransform()->SetLocalScaling(float4{ 20.f,27.f,1.f });
		UICard_[i]->SetChangeAnimation("BottomCard_Dia");


		//UICard_[i]->SetRenderingPipeLine("ProgressBar");

		//UICard_[i]->ShaderHelper.SettingConstantBufferLink("ProgressBarCBuffer", ProgressBarData_);
		//UICard_[i]->ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData_);

		//float4 ResultColor_ = float4::ONE;
		//UICard_[i]->ShaderHelper.SettingConstantBufferLink("ResultColor", ResultColor_);

		UICard_[i]->Off();
	}
}

void Bottom_Card::Update(float _DeltaTime)
{
	for (int i = 0; i < CurCount_; ++i)
	{
		UICard_[i]->On();
	}

	for (int i = CurCount_; i < 6; ++i)
	{
		UICard_[i]->Off();
	}

	//if (WaitingCount_ != 0)
	//{
	//	UICard_[RiseingIndex_]->On();
	//	UICard_[RiseingIndex_]->GetTransform()->SetLocalMove(float4{0.f,50.f* _DeltaTime ,0.f});

	//	if (UICard_[RiseingIndex_]->GetTransform()->GetLocalPosition().y >= 0.f)
	//	{
	//		UICard_[RiseingIndex_]->GetTransform()->SetLocalPosition(float4{ 50.f * RiseingIndex_,-50.f,1.f });

	//		--WaitingCount_;
	//		++CurCount_;
	//		RiseingIndex_ = CurCount_ +1;
	//		//올라오는중에 끊기지 않도록 조정할것, 혹은 올라오는중에 끊기게끔 조정할것

	//	}
	//	//정확히 재자리에 오기까지 기다리고 끝

	//	// curcount에 맞는 렌더러가 위로 올라옴
	//}
}

void Bottom_Card::Increase()
{
	if (CurCount_ != 6)
	{
		++CurCount_;
	}
}

void Bottom_Card::Decrease()
{
	if (CurCount_ != 0)
	{
		--CurCount_;
	}
}

void Bottom_Card::Resset()
{
	for (int i = 0; i < 6; ++i)
	{
		UICard_[i]->Off();
	}

	//CurCount_ = 0;
	//WaitingCount_ = 0;
	//RiseingIndex_ = 0;

	//미완ㅅ6ㅓㅇ
}

