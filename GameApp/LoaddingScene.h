#pragma once
//#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineFSM.h>
#include "SceneBase.h"

// ���� :
class LoaddingScene : public SceneBase
{
	friend class TitleScene;
public:
	LoaddingScene(); // default constructer ����Ʈ ������
	~LoaddingScene(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LoaddingScene(const LoaddingScene& _other) = delete; // default Copy constructer ����Ʈ ���������
	LoaddingScene(LoaddingScene&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	LoaddingScene& operator=(const LoaddingScene& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LoaddingScene& operator=(const LoaddingScene&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:	// member Var
	std::string NextScene_;
	std::string PrevScene_;

	class Image* HourGlass_;

	GameEngineFSM PhaseState_;

	bool LoadEnd_;
	bool CutIn_;
	bool LevelDestroy_;

protected:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

private:

public:
	void SetLoaddingNextLevel(std::string _PrevScene_,std::string _Nextlevel, bool _LevelDestroy = true)
	{
		LevelDestroy_ = _LevelDestroy;
		PrevScene_ = _PrevScene_;
		NextScene_ = _Nextlevel;
	}

	void LoadEnd()
	{
		LoadEnd_ = true;
	}
};

