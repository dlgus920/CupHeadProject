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

LoaddingScene::~LoaddingScene() // default destructer 디폴트 소멸자
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
				0. 레벨을 만들어만 놓고 리소스는 로드해 두지 않음,
				1. 로딩 씬에서 리소스를 로드하고, 로드 완료시 스타트 호출

				1. LevelCreate는 리소스 로드만 담당하게 한다.

				2. LoaddingScene에서 리소스 로드가 끝났는지를 체크하고, 씬을 넘겨준다.
				3. LoaddingScene에서 리소스 로드가 끝났음을 체크하고, 딱1번 실행시킬 함수를 정하던가
				4. 매번 씬을 넘길때마다 LevelStart를 호출하고, 이전 씬을 지워버린다.

				4-1. DicePalce의 경우, 다시 되돌아올때, 진행 상황을 어디선가 가지고 있다가 이쪽으로 다시 가져와 줘야 한다.
				아마도 플레이어가 진행 상황을 가지고 있으면 될것 같다. 레벨 시작할때마다 플레이어에게서 가져오고 그대로 셋팅하도록 하자
				
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
