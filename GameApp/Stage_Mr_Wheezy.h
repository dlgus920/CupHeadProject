#pragma once
#include <GameEngineBase/GameEngineFSM.h>
#include "SceneBase.h"

#include <GameEngineBase/GameEngineRandom.h>

class Stage_Mr_Wheezy : public SceneBase
{

public:
	Stage_Mr_Wheezy();
	~Stage_Mr_Wheezy();

protected:		// delete constructer
	Stage_Mr_Wheezy(const Stage_Mr_Wheezy& _other) = delete;
	Stage_Mr_Wheezy(Stage_Mr_Wheezy&& _other) = delete;
	Stage_Mr_Wheezy& operator=(const Stage_Mr_Wheezy& _other) = delete;
	Stage_Mr_Wheezy& operator=(const Stage_Mr_Wheezy&& _other) = delete;

private:

	class Mr_Wheezy* Mr_Wheezy_;
	class Flying_Cigar* Flying_Cigar_;
	class GameEngineImageRenderer* BackImageRenderer_[2];
	//class Player* Player_;
	//bool Victory_;

	class GameEngineRandom Random_;
	std::string NextScene_;


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
	GameEngineFSM<Stage_Mr_Wheezy> LoadState_;

	void Init_Update(float _DeltaTime);

	void ResourcesLoad_Start();
	void ResourcesLoad_Update(float _DeltaTime);

	void LevelLoop_Start();
	void LevelLoop_Update(float _DeltaTime);

private:
	GameEngineFSM<Stage_Mr_Wheezy> PhaseState_;

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Playing_Start();
	void Playing_Update(float _DeltaTime);
	void Playing_End();


public:
	void SetNextScene(std::string _NextScene)
	{
		NextScene_ = _NextScene;
	}

};

