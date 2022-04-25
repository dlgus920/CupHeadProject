#pragma once
//#include <GameEngine/GameEngineLevel.h>
#include "SceneBase.h"

// ���� :
class LoaddingScene : public SceneBase
{
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
	class Image* HourGlass_;
	bool LoadEnd_;

	bool CutIn_;

protected:
	void LevelResourcesLoad() override;
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;
public:
	void SetLoaddingNextLevel(std::string _Nextlevel)
	{
		NextScene_ = _Nextlevel;
	}

	void LoadEnd()
	{
		LoadEnd_ = true;
	}
};

