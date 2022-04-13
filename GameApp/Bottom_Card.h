#pragma once
#include "UIBase.h"

enum class UICardType
{
	Spade,
	Dia
};

enum class ProgressBarDirect
{
	BottomToTop,		// Bottom -> Top
	TopToBottom,		// Top -> Bottom
	RightToLeft,		// Right -> Left
	LeftToRight			// Left -> Right
};

struct ProgressBarCBuffer
{
	ProgressBarCBuffer() 
		: Percent(1.f)
		, PregressDirection(0)
		, Empty1(0.f)
		, Empty2(0.f)
	{
	}

	float Percent;
	int PregressDirection;
	float Empty1;
	float Empty2;

};

class Bottom_Card : public UIBase
{
public:
	Bottom_Card();
	~Bottom_Card();

private:	
	Bottom_Card(const Bottom_Card& _other) = delete;
	Bottom_Card(Bottom_Card&& _other) = delete;
	Bottom_Card& operator=(const Bottom_Card& _other) = delete;
	Bottom_Card& operator=(const Bottom_Card&& _other) = delete;

private:

	ProgressBarCBuffer ProgressBarData_;
	float4 CutData_;

	int CurCount_;
	int RiseingIndex_;
	int WaitingCount_;
	bool WorkEnd_;

	float4 CardPos_[6];
	class GameEngineImageRenderer* UICard_[6];

	//게이지가 즉각즉각 차는게 아니라 대기열로 존재하면서 채워지게끔, 지워지는것도 마찬가지 업데이트에서 대기열로 처리,

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void Increase();
	void Decrease();

	int GetCardCount()
	{
		return CurCount_;
	}

	void Resset();

public:
	void UIChaneCardType(UICardType _UICardType)
	{
		if (_UICardType == UICardType::Dia)
		{
			UICard_[CurCount_]->SetChangeAnimation("BottomCard_Dia");
		}
		else
		{
			UICard_[CurCount_]->SetChangeAnimation("BottomCard_Spade");
		}
	}
};

