#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImageRenderer;
class Effect : public GameEngineActor
{
public:
	Effect();
	~Effect();

private:
	Effect(const Effect& _other) = delete;
	Effect(Effect&& _other) = delete;
	Effect& operator=(const Effect& _other) = delete;
	Effect& operator=(const Effect&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	GameEngineImageRenderer* AddImageAnimationActor(std::string _TextureName, std::string _AnimationName, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop);
	GameEngineImageRenderer* AddImageAnimationFolderActor(std::string _TextureName, std::string _AnimationName , float _InterTime, bool _Loop);



};