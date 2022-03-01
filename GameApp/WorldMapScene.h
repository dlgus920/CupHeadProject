#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� :
class WorldMapScene : public GameEngineLevel
{
private:	// member Var

public:
	WorldMapScene(); // default constructer ����Ʈ ������
	~WorldMapScene(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WorldMapScene(const WorldMapScene& _other) = delete; // default Copy constructer ����Ʈ ���������
	WorldMapScene(WorldMapScene&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WorldMapScene& operator=(const WorldMapScene& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WorldMapScene& operator=(const WorldMapScene&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};
