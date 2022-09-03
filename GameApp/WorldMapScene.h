#pragma once
#include <GameEngineBase/GameEngineFSM.h>

#include "SceneBase.h"

#include "WorldMapPlayer.h"

// ���� :
class WorldMapScene : public SceneBase
{
	friend class LoaddingScene;

public:
	WorldMapScene(); // default constructer ����Ʈ ������
	~WorldMapScene(); // default destructer ����Ʈ �Ҹ���

	WorldMapScene(const WorldMapScene& _other) = delete; // default Copy constructer ����Ʈ ���������
	WorldMapScene(WorldMapScene&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	WorldMapScene& operator=(const WorldMapScene& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WorldMapScene& operator=(const WorldMapScene&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	class WorldMapPlayer* WorldMapPlayer_;
	class Image* IrisImage_;

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
	void ChangeScene(std::string _Scene);

	friend void WorldMapPlayer::ChangeScene(std::string _Scene);

	void SetScreenIris(bool _In);

	void ScreenFadeEnd();
	bool ScreenFadeEnd_;
public:

};
