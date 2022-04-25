#pragma once
#include <GameEngine/GameEngineLevel.h>

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

public:

	class Image* FadeImage_;
	float TimeCheck_;
	float BlendRate_;

protected:
	virtual void LevelResourcesLoad();
	virtual void LevelStart();
	virtual void LevelUpdate(float _DeltaTime);
	virtual void LevelChangeEndEvent();
	virtual void LevelChangeStartEvent();

	void TextureLoading(GameEngineDirectory Dir);
	

};

