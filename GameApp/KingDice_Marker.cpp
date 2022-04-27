#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "KingDice_Marker.h"


KingDice_Marker::KingDice_Marker()
	: NumRenderer_{ nullptr }
	, ClearRenderer_{nullptr}
{

}

KingDice_Marker::~KingDice_Marker() // default destructer 디폴트 소멸자
{

}

void KingDice_Marker::Start()
{
	for (int i = 0; i < 11; ++i)
	{
		NumRenderer_[i] = CreateTransformComponent<GameEngineImageRenderer>();
		ClearRenderer_[i] = CreateTransformComponent<GameEngineImageRenderer>();
		NumRenderer_[i]->GetTransform()->SetLocalScaling(float4{ 870.f,400.f });
		ClearRenderer_[i]->GetTransform()->SetLocalScaling(float4{ 870.f,400.f });
		ClearRenderer_[i]->Off();


	}

	{
		NumRenderer_[0]->	SetImage("Num_001.png");
		NumRenderer_[1]->	SetImage("Num_002.png");
		NumRenderer_[2]->	SetImage("Num_003.png");
		NumRenderer_[3]->	SetImage("Num_004.png");
		NumRenderer_[4]->	SetImage("Num_005.png");
		NumRenderer_[5]->	SetImage("Num_006.png");
		NumRenderer_[6]->	SetImage("Num_007.png");
		NumRenderer_[7]->	SetImage("Num_008.png");
		NumRenderer_[8]->	SetImage("Num_009.png");
		NumRenderer_[9]->	SetImage("Num_010.png");
		NumRenderer_[10]->	SetImage("Num_011.png");
	}

	{
		ClearRenderer_[0]->		SetImage("Clear_001.png");
		ClearRenderer_[1]->		SetImage("Clear_002.png");
		ClearRenderer_[2]->		SetImage("Clear_003.png");
		ClearRenderer_[3]->		SetImage("Clear_004.png");
		ClearRenderer_[4]->		SetImage("Clear_005.png");
		ClearRenderer_[5]->		SetImage("Clear_006.png");
		ClearRenderer_[6]->		SetImage("Clear_007.png");
		ClearRenderer_[7]->		SetImage("Clear_008.png");
		ClearRenderer_[8]->		SetImage("Clear_009.png");
		ClearRenderer_[9]->		SetImage("Clear_010.png");
		ClearRenderer_[10]->	SetImage("Clear_011.png");
	}
}

void KingDice_Marker::Update(float _DeltaTime)
{

}

void KingDice_Marker::Clear(int Num)
{
	ClearRenderer_[Num]->On();
	NumRenderer_[Num]->Off();
}

void KingDice_Marker::AllClear()
{
	for (int i = 0; i < 11; ++i)
	{
		ClearRenderer_[i]->On();
		NumRenderer_[i]->Off();
	}
}
