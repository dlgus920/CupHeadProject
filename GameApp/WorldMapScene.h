#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "WorldMapPlayer.h"

// ���� :
class WorldMapScene : public GameEngineLevel
{

public:
	WorldMapScene(); // default constructer ����Ʈ ������
	~WorldMapScene(); // default destructer ����Ʈ �Ҹ���

	WorldMapScene(const WorldMapScene& _other) = delete; // default Copy constructer ����Ʈ ���������
	WorldMapScene(WorldMapScene&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	WorldMapScene& operator=(const WorldMapScene& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WorldMapScene& operator=(const WorldMapScene&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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
