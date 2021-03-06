#pragma once
#include <GameEngineBase/GameEngineFSM.h>

#include "SceneBase.h"

#include "WorldMapPlayer.h"

// 설명 :
class WorldMapScene : public SceneBase
{
	friend class LoaddingScene;

public:
	WorldMapScene(); // default constructer 디폴트 생성자
	~WorldMapScene(); // default destructer 디폴트 소멸자

	WorldMapScene(const WorldMapScene& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WorldMapScene(WorldMapScene&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	WorldMapScene& operator=(const WorldMapScene& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WorldMapScene& operator=(const WorldMapScene&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	class WorldMapPlayer* WorldMapPlayer_;
	class Image* IrisImage_;

	std::string NextScene_;

private:	
	GameEngineFSM<WorldMapScene> LoadState_;

	void Init_Update(float _DeltaTime);

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
	void ChangeScene(std::string _Scene);

	friend void WorldMapPlayer::ChangeScene(std::string _Scene);

	void SetScreenIris(bool _In);


	void ScreenFadeEnd();
	bool ScreenFadeEnd_;
public:

};
