#include "PreCompile.h"
#include "Bottom_Card.h"

Bottom_Card::Bottom_Card()
	: CurCount_(0)
	, WaitingCount_(0)
	, RiseingIndex_(0)
	, Player_(nullptr)
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
	for (int i = 0; i < 6; ++i)
	{
		UICard_[i] = CreateTransformComponent<GameEngineImageRenderer>();
		UICard_[i]->CreateAnimation("BottomCard_Dia.png", "BottomCard_Dia", 0, 5, 0.1f);
		UICard_[i]->CreateAnimation("BottomCard_Spade.png", "BottomCard_Spade", 0, 5, 0.1f);
		UICard_[i]->GetTransform()->SetLocalPosition(float4{30.f * i,-50.f,1.f});
		UICard_[i]->GetTransform()->SetLocalScaling(float4{ 20.f,27.f,1.f });
		UICard_[i]->SetChangeAnimation("BottomCard_Dia");
		//UICard_[i]->Off();
	}
}

void Bottom_Card::Update(float _DeltaTime)
{
	//if (WaitingCount_ != 0)
	//{
	//	UICard_[RiseingIndex_]->On();
	//	UICard_[RiseingIndex_]->GetTransform()->SetLocalMove(float4{0.f,30.f* _DeltaTime ,0.f});

	//	if (UICard_[RiseingIndex_]->GetTransform()->GetLocalPosition().y >= 0.f)
	//	{
	//		UICard_[RiseingIndex_]->GetTransform()->SetLocalPosition(float4{ 50.f * RiseingIndex_,-50.f,1.f });

	//		--WaitingCount_;
	//		++RiseingIndex_;
	//		++CurCount_;
	//		//올라오는중에 끊기지 않도록 조정할것, 혹은 올라오는중에 끊기게끔 조정할것

	//	}
	//	//정확히 재자리에 오기까지 기다리고 끝

	//	// curcount에 맞는 렌더러가 위로 올라옴
	//}



}

void Bottom_Card::Increase()
{
	++WaitingCount_;
}

void Bottom_Card::Decrease()
{
	--WaitingCount_;
}

void Bottom_Card::Resset()
{
	for (int i = 0; i < 6; ++i)
	{
		UICard_[i]->Off();
	}

	CurCount_ = 0;
	WaitingCount_ = 0;
	RiseingIndex_ = 0;

	//미완ㅅ6ㅓㅇ
}

