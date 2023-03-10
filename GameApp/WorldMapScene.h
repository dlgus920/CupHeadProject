#pragma once
#include <GameEngineBase/GameEngineFSM.h>

#include "SceneBase.h"

#include "WorldMapPlayer.h"

// Ό³Έν :
class WorldMapScene : public SceneBase
{
	friend class LoaddingScene;

public:
	WorldMapScene(); 
	~WorldMapScene();

	WorldMapScene(const WorldMapScene& _other) = delete; 
	WorldMapScene(WorldMapScene&& _other) = delete; 
	WorldMapScene& operator=(const WorldMapScene& _other) = delete; 
	WorldMapScene& operator=(const WorldMapScene&& _other) = delete; 

public:
	class WorldMapPlayer* WorldMapPlayer_;
	class Image* IrisImage_;

	GameEngineImageRenderer* DEBUGBack_Image_;
	GameEngineCollision* DeBugStage_Point_;

	std::string NextScene_;

private:	
	GameEngineFSM LoadState_;

	void ResourcesLoad_Start();
	void ResourcesLoad_Update(float _DeltaTime);
	void ResourcesLoad_End();

	void LevelLoop_Start();
	void LevelLoop_Update(float _DeltaTime);
	void LevelLoop_End();

	void LevelEnd_Start();
	void LevelEnd_Update(float _DeltaTime);
	void LevelEnd_End();

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

private:
	void KeySetting();

	void ChangeScene(std::string _Scene);

	friend void WorldMapPlayer::ChangeScene(std::string _Scene);

	void SetScreenIris(bool _In);

	void ScreenFadeEnd();
	bool ScreenFadeEnd_;

public:

};
