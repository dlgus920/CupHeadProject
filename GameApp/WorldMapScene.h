#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "WorldMapPlayer.h"

// 설명 :
class WorldMapScene : public GameEngineLevel
{

public:
	WorldMapScene(); // default constructer 디폴트 생성자
	~WorldMapScene(); // default destructer 디폴트 소멸자

	WorldMapScene(const WorldMapScene& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WorldMapScene(WorldMapScene&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	WorldMapScene& operator=(const WorldMapScene& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WorldMapScene& operator=(const WorldMapScene&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	class WorldMapPlayer* WorldMapPlayer_;

private:	// member Var

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

private:
	void ChangeScene(std::string _Scene);

	friend void WorldMapPlayer::ChangeScene(std::string _Scene);
};
