#pragma once
#include <GameEngineBase/GameEngineFSM.h>
#include "SceneBase.h"

#include <GameEngineBase/GameEngineRandom.h>

class DicePaclace : public SceneBase
{
public:
	DicePaclace(); 
	~DicePaclace(); 

protected:		// delete constructer
	DicePaclace(const DicePaclace& _other) = delete; 
	DicePaclace(DicePaclace&& _other) = delete; 
	DicePaclace& operator=(const DicePaclace& _other) = delete; 
	DicePaclace& operator=(const DicePaclace&& _other) = delete; 

private:	
	class GameEngineRandom Random_;

	GameEngineFSM PhaseState_;
	GameEngineFSM LoadState_;

	class King_Dice* King_Dice_;
	class KingDice_Marker* KingDice_Marker_;
	class GameEngineImageRenderer* NumRenderer_[11];

	std::string NextScene_;

	int StageMoveCount_;
	int CurStageNum_; //max 10
	int NextStageNum_; //max 10

	bool IsStageMove_;
	bool MoveEnd_;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

public:

	void SetPlusDiceNum(int _num)
	{
		StageMoveCount_ = _num; 
		IsStageMove_ = true;
	}

private:

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Playing_Start();
	void Playing_Update(float _DeltaTime);
	void Playing_End();

	void PlayingEnd_Start();
	void PlayingEnd_Update(float _DeltaTime);

private:
	void ResourcesLoad_Start();
	void ResourcesLoad_Update(float _DeltaTime);

	void LevelLoop_Start();
	void LevelLoop_Update(float _DeltaTime);


public:
	void SetNextScene(std::string _NextScene)
	{
		NextScene_ = _NextScene;
	}
};

