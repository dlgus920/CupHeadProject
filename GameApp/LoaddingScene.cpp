#include "PreCompile.h"
#include <GameEngine/GameEngineCore.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "UserGame.h"

#include "LoaddingScene.h"
#include "WorldMapScene.h"
#include "Stage_Mr_Wheezy.h"
#include "DicePaclace.h"

#include "Image.h"

LoaddingScene::LoaddingScene() 
	: PhaseState_(this)
	, NextScene_()
	, PrevScene_()
	, LoadEnd_(false)
	, CutIn_(false)
	, LevelDestroy_(false)
	, HourGlass_(nullptr)
{

}

LoaddingScene::~LoaddingScene() // default destructer ����Ʈ �Ҹ���
{
}

void LoaddingScene::LevelStart()
{
	//{
	//	Image* Back = CreateActor<Image>();
	//	Back->ImageSetImage("Loading_background.png");
	//	Back->GetTransform()->SetWorldPosition(float4(0.f, 0.0f, static_cast<int>(ZOrder::Z02Back01)));
	//	Back->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f });

	//	BlendRate_ = 1.f;

	//	FadeImage_ = CreateActor<Image>();

	//	FadeImage_->ImageRenderer_->SetImage("title_screen_background.png");
	//	FadeImage_->GetTransform()->SetWorldPosition(float4{ 0.f, 0.f, static_cast<float>(ZOrder::Z00Fx00) });
	//	FadeImage_->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f });
	//	FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
	//}
}

void LoaddingScene::LevelUpdate(float _DeltaTime)
{

	if (BlendRate_ >= 1.f)
	{
		CutIn_ = true;
	}

	if (true == CutIn_)
	{
		BlendRate_ -= _DeltaTime * 2;

		if (BlendRate_ < 0.f)
		{
			BlendRate_ = 0.f;

			CutIn_ = false;
		}
		FadeImage_->ImageRenderer_-> SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });

	}
	else
	{
		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 1.f && 0 >= UserGame::LoadingFolder)
		{
			BlendRate_ += _DeltaTime * 2;

			if (BlendRate_ >= 1.f )
			{
				//GameEngineCore::LevelFind(NextScene_)->LevelChangeStartEvent(nullptr);

				/*
				TODO: 
				0. ������ ���� ���� ���ҽ��� �ε��� ���� ����,
				1. �ε� ������ ���ҽ��� �ε��ϰ�, �ε� �Ϸ�� ��ŸƮ ȣ��

				1. LevelCreate�� ���ҽ� �ε常 ����ϰ� �Ѵ�.

				2. LoaddingScene���� ���ҽ� �ε尡 ���������� üũ�ϰ�, ���� �Ѱ��ش�.
				3. LoaddingScene���� ���ҽ� �ε尡 �������� üũ�ϰ�, ��1�� �����ų �Լ��� ���ϴ���
				4. �Ź� ���� �ѱ涧���� LevelStart�� ȣ���ϰ�, ���� ���� ����������.

				4-1. DicePalce�� ���, �ٽ� �ǵ��ƿö�, ���� ��Ȳ�� ��𼱰� ������ �ִٰ� �������� �ٽ� ������ ��� �Ѵ�.
				�Ƹ��� �÷��̾ ���� ��Ȳ�� ������ ������ �ɰ� ����. ���� �����Ҷ����� �÷��̾�Լ� �������� �״�� �����ϵ��� ����
				
				*/
				//GameEngineCore::LevelFind(NextScene_)->LevelResourcesLoad();

				GameEngineCore::LevelFind(NextScene_)->LevelStart();

				GameEngineCore::LevelChange(NextScene_);

				if (true == LevelDestroy_)
				{
					GameEngineCore::LevelDestroy(PrevScene_);
				}
				PrevScene_.clear();
				NextScene_.clear();
				LoadEnd_ = false;
				HourGlass_->Death();
				HourGlass_ = nullptr;
			}
			FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
		}
	}
}

void LoaddingScene::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}

void LoaddingScene::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -static_cast<int>(ZOrder::Z00Camera00)));

	HourGlass_ = CreateActor<Image>();
	HourGlass_->GetTransform()->SetWorldPosition(float4(450.f, -180.0f, static_cast<int>(ZOrder::Z01Actor02)));
	HourGlass_->ImageRenderer_->GetTransform()->SetLocalScaling(float4{200.f,320.f});
	HourGlass_->ImageCreateAnimation("HourGlass.png", "HourGlass", 0, 45, 0.05f, true);
	HourGlass_->ImageRenderer_->SetEndCallBack("HourGlass", std::bind(&LoaddingScene::LoadEnd, this));

	GameEngineCore::LevelFind(NextScene_)->LevelResourcesLoad();
}
