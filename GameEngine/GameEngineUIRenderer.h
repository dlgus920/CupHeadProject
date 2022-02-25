#pragma once
#include "GameEngineRenderer.h"

// ���� : �ϳ��� ���� ������ ǥ���մϴ�.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineRenderer
{
private:
	friend GameEngineLevel;
	friend CameraComponent;

public:
	// constrcuter destructer
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

	// delete Function
	GameEngineUIRenderer(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer(GameEngineUIRenderer&& _Other) noexcept = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer& operator=(GameEngineUIRenderer&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
};

