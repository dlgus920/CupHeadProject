#include "PreCompile.h"
#include "DicePaclace.h"
#include "LoaddingScene.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/MouseActor.h>
#include <GameEngine/GameEngineCore.h>
//#include <GameEngineBase/GameEngineRandom.h>

#include "UserGame.h"

#include "Map.h"
#include "Image.h"
#include "KingDice_Marker.h"
#include "Effect.h"
#include "PerryObjectDice.h"
#include "King_Dice.h"
#include "Player.h"

DicePaclace::DicePaclace() 
	: King_Dice_(nullptr)
	, PhaseState_(this)
	, LoadState_(this)
	, ScreenFx(nullptr)
	, KingDice_Marker_(nullptr)
	, IsStageMove_(false)
	, MoveEnd_(false)
	, CurStageNum_(0)
	, StageMoveCount_(0)
{
}

DicePaclace::~DicePaclace() // default destructer 디폴트 소멸자
{
}
void DicePaclace::LevelStart()
{
	GameEngineInput::GetInst().CreateKey("FreeCameraOn", 'o');

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<float>(ZOrder::Z00Camera00)));

	PhaseState_.CreateState("Intro", &DicePaclace::Intro_Start, &DicePaclace::Intro_Update, &DicePaclace::Intro_End);
	PhaseState_.CreateState("Playing", &DicePaclace::Playing_Start, &DicePaclace::Playing_Update, &DicePaclace::Playing_End);

	PhaseState_.ChangeState("Intro");

	LoadState_.CreateState("ResourcesLoad", &DicePaclace::ResourcesLoad_Start, &DicePaclace::ResourcesLoad_Update, &DicePaclace::ResourcesLoad_End);
	LoadState_.CreateState("LevelLoop", &DicePaclace::LevelLoop_Start, &DicePaclace::LevelLoop_Update, &DicePaclace::LevelLoop_End);
	LoadState_.CreateState("Init", nullptr, &DicePaclace::Init_Update, nullptr);
}
void DicePaclace::LevelUpdate(float _DeltaTime)
{
	LoadState_.Update(_DeltaTime);

	if (true == GameEngineInput::GetInst().Down("FreeCameraOn"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}
}

void DicePaclace::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}
void DicePaclace::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	LoadState_.ChangeState("Init");
}

void DicePaclace::Intro_Start()
{
}
void DicePaclace::Intro_Update(float _DeltaTime)
{
	BlendRate_ -= _DeltaTime;
	if (0.f >= BlendRate_)
	{
		BlendRate_ = 0.f;

		PhaseState_.ChangeState("Playing");
		return;
	}

	FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });

}
void DicePaclace::Intro_End()
{
}

void DicePaclace::Playing_Start()
{
	//NextScene_ = "WorldMap";

	ReadyWALLOP();
}
void DicePaclace::Playing_Update(float _DeltaTime)
{
	if (true == IsStageMove_)
	{
		KingDice_Marker_->Clear(StageMoveCount_);
	}

	if (true == Victory_)
	{
		int ranint = Random_.RandomInt(-10,10);

		GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f + ranint, static_cast<float>(ZOrder::Z00Camera00)));

		TimeCheck_ += _DeltaTime;

		if (TimeCheck_ > 3.f)
		{
			BlendRate_ += _DeltaTime;
			FadeImage_->ImageRenderer_->SetResultColor(float4{ 0.f,0.f,0.f,BlendRate_ });
		}

		if (BlendRate_ >= 1.f)
		{
			BlendRate_ = 1.f;

			GameEngineCore::LevelChange("WorldMap");
		}
	}
}
void DicePaclace::Playing_End()
{
}