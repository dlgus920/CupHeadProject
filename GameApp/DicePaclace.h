#pragma once
#include <GameEngineBase/GameEngineFSM.h>
#include "SceneBase.h"

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
	GameEngineFSM<DicePaclace> PhaseState_;

	class King_Dice* King_Dice_;
	class Player* Player_;

	std::string NextScene_;

	bool Victory_;

private:
	void LevelResourcesLoad() override;
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

public:
	void GamePlayVictory();
	void GamePlayStart();
	void KnockoutEnd();

private:
	void ResourcesLoading_Start();
	void ResourcesLoading_Update(float _DeltaTime);
	void ResourcesLoading_End();

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Playing_Start();
	void Playing_Update(float _DeltaTime);
	void Playing_End();

	//void End_Start();
	//void End_Update(float _DeltaTime);
	//void End_End();

public:
	//friend void WorldMapPlayer::ChangeScene(std::string _Scene);

	void SetNextScene(std::string _NextScene)
	{
		NextScene_ = _NextScene;
	}
};

