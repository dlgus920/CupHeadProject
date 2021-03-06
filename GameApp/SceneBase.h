#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineSoundPlayer.h>

class SceneBase : public GameEngineLevel
{
private:	// member Var

public:
	SceneBase();
	~SceneBase();

	SceneBase(const SceneBase& _other) = delete;
	SceneBase(SceneBase&& _other) = delete;
	SceneBase& operator=(const SceneBase& _other) = delete;
	SceneBase& operator=(const SceneBase&& _other) = delete;

	class Image* FadeImage_;
	float TimeCheck_;
	float BlendRate_;

protected:

	class GameEngineSoundPlayer* SceneBGM_;
	class GameEngineSoundPlayer* IntroBGM_;

	class Player* Player_;
	class Image* HourGlass_;
	bool Victory_;

	bool LoadingComplete_;
	bool LoadingFadeComplete_;


//public:
//
//	struct StageInfo
//	{
//		bool Dice_ClearStage_[9];
//		float4 WorldMapPlayer_Pos_;
//	};
//
//	static StageInfo StageInfo_;
//
//	//StageInfo GetStageInfo()
//	//{
//	//	return StageInfo_;
//	//}
//
//public:
//	void SetStageInfo(StageInfo _StageInfo)
//	{
//		StageInfo_ = _StageInfo;
//	}
protected:

	void PlayerResourceLoad();
	void SceneResourceLoad();

	void ResourcesLoadFadeInit();
	void LevelLoadFadeUpdate(float _DeltaTime);
	//void ResourcesLoadFadeUpdate(float _DeltaTime);
	//void SceneResourceClear();

	void ReadyWALLOPAnounce01();
	void ReadyWALLOPAnounce02();

	//void JobPostres(GameEngineDirectory Dir);
	//void JobPostresinst(std::vector<GameEngineFile>* AllFile, int arraycount);


public:
	void Knockout();
	void ReadyWALLOP();
	void ReadyWALLOP_DICE();
	void KnockoutEnd();

protected:
	virtual void LevelStart();
	virtual void LevelUpdate(float _DeltaTime);

	virtual void LevelChangeEndEvent();
	virtual void LevelChangeStartEvent();

protected:

};

