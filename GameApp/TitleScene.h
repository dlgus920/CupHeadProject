#pragma once
#include "SceneBase.h"
#include <GameEngineBase/GameEngineFSM.h>

// Ό³Έν :
class TitleScene : public SceneBase
{
public:
	// constrcuter destructer
	TitleScene();
	~TitleScene();

	// delete Function
	TitleScene(const TitleScene& _Other) = delete;
	TitleScene(TitleScene&& _Other) noexcept = delete;
	TitleScene& operator=(const TitleScene& _Other) = delete;
	TitleScene& operator=(TitleScene&& _Other) = delete;

protected:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;
private:
	void ResourcesLoad_Start();
	void ResourcesLoad_Update(float _DeltaTime);
	void ResourcesLoad_End();

	void LevelLoop_Start();
	void LevelLoop_Update(float _DeltaTime);
	void LevelLoop_End();

private:	
	GameEngineFSM LoadState_;
	class GameEngineImageRenderer* FontImageRenderer;
	bool TobeNext_;
	bool end_;

	bool SceneStart_;
	float timecheck_;
};

