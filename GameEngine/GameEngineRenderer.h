#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// ���� : �ϳ��� ���� ������ ǥ���մϴ�.
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

