#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� :
class StoryScene : public GameEngineLevel
{
private:	// member Var

public:
	StoryScene(); // default constructer ����Ʈ ������
	~StoryScene(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	StoryScene(const StoryScene& _other) = delete; // default Copy constructer ����Ʈ ���������
	StoryScene(StoryScene&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	StoryScene& operator=(const StoryScene& _other) = delete; // default Copy operator ����Ʈ ���� ������
	StoryScene& operator=(const StoryScene&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};
