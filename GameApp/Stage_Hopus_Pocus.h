#pragma once
#include <GameEngineBase/GameEngineFSM.h>
#include "SceneBase.h"

#include <GameEngineBase/GameEngineRandom.h>

class Stage_Hopus_pocus : public SceneBase
{

public:
	Stage_Hopus_pocus();
	~Stage_Hopus_pocus();

protected:		// delete constructer
	Stage_Hopus_pocus(const Stage_Hopus_pocus& _other) = delete;
	Stage_Hopus_pocus(Stage_Hopus_pocus&& _other) = delete;
	Stage_Hopus_pocus& operator=(const Stage_Hopus_pocus& _other) = delete;
	Stage_Hopus_pocus& operator=(const Stage_Hopus_pocus&& _other) = delete;

private:

	class Hopus_pocus* Hopus_pocus_;
	class Floating_Card* Floating_Card_;
	class GameEngineImageRenderer* BackRightImageRenderer_[2];

	float4 LightBlendRate_[2];
	bool LightBlendCheck_;

	class GameEngineRandom Random_;


private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

//public:
//	void Knockout();
//	void ReadyWALLOP();
//	void KnockoutEnd();
private:
	GameEngineFSM LoadState_;

	void ResourcesLoad_Start();
	void ResourcesLoad_Update(float _DeltaTime);

	void LevelLoop_Start();
	void LevelLoop_Update(float _DeltaTime);

private:
	GameEngineFSM PhaseState_;

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Playing_Start();
	void Playing_Update(float _DeltaTime);
	void Playing_End();
};

