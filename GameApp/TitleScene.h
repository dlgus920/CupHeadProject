#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class TitleScene : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleScene();
	~TitleScene();

	// delete Function
	TitleScene(const TitleScene& _Other) = delete;
	TitleScene(TitleScene&& _Other) noexcept = delete;
	TitleScene& operator=(const TitleScene& _Other) = delete;
	TitleScene& operator=(TitleScene&& _Other) = delete;

protected:
	void LevelResourcesLoad() override;
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

private:
	class Image* FadeImage_;

	bool TobeNext_;
	float BlendRate_;
};

