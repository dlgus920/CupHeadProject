#pragma once
#include <GameEngine/GameEngineLevel.h>

// 설명 :
class StoryScene : public GameEngineLevel
{
private:	// member Var

public:
	StoryScene(); // default constructer 디폴트 생성자
	~StoryScene(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	StoryScene(const StoryScene& _other) = delete; // default Copy constructer 디폴트 복사생성자
	StoryScene(StoryScene&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	StoryScene& operator=(const StoryScene& _other) = delete; // default Copy operator 디폴트 대입 연산자
	StoryScene& operator=(const StoryScene&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};
