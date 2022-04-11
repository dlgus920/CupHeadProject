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
	�����ؾ��Ұ�,
	���� �� ī�� ����
	���� �ö���� �ִ� ī���� ��ȣ
	���� ������� ī�� ����

	
	
	*/



	Player* Player_;
	int CurCount_;
	int RiseingIndex_;
	int WaitingCount_;
	bool WorkEnd_;

	float4 CardPos_[6];
	GameEngineImageRenderer* UICard_[6];

	//�������� �ﰢ�ﰢ ���°� �ƴ϶� ��⿭�� �����ϸ鼭 ä�����Բ�, �������°͵� �������� ������Ʈ���� ��⿭�� ó��,

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

