#pragma once
#include "UIBase.h"

enum class UICardType
{
	Spade,
	Dia
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
	/*
	구분해야할것,
	현재 총 카드 갯수
	현재 올라오고 있는 카드의 번호
	현재 대기중인 카드 갯수

	
	
	*/



	Player* Player_;
	int CurCount_;
	int RiseingIndex_;
	int WaitingCount_;
	bool WorkEnd_;

	float4 CardPos_[6];
	GameEngineImageRenderer* UICard_[6];

	//게이지가 즉각즉각 차는게 아니라 대기열로 존재하면서 채워지게끔, 지워지는것도 마찬가지 업데이트에서 대기열로 처리,

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Increase();
	void Decrease();

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
	void SetUIPlayer (Player* _Player)
	{
		Player_ = _Player;
	}
};

