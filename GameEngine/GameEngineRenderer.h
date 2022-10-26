#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// 설명 : 하나의 랜더 단위를 표현합니다.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
private:
	friend GameEngineLevel;
	friend CameraComponent;

	void Update(float _DeltaTime) override;

public:
	GameEngineShaderResHelper ShaderHelper;

	void SetRenderingPipeLine(const std::string& _Value);

	virtual void SetRenderingPipeLineSettingNext() {}
	virtual void SetRenderGroup(int _Order);

protected:
	GameEngineRenderingPipeLine* PipeLine_;

	void Start() override;

	virtual void Render();

public:
	GameEngineRenderer();
	~GameEngineRenderer();

	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) = delete;

};

