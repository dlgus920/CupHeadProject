#pragma once
//#include <GameEngine/GameEngineLevel.h>
#include "SceneBase.h"

// 설명 :
class LoaddingScene : public SceneBase
{
public:
	LoaddingScene(); // default constructer 디폴트 생성자
	~LoaddingScene(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LoaddingScene(const LoaddingScene& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LoaddingScene(LoaddingScene&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	LoaddingScene& operator=(const LoaddingScene& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LoaddingScene& operator=(const LoaddingScene&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

