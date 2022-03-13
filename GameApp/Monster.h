#pragma once
#include "GameObject.h"
#include <GameEngine/GameEngineImageRenderer.h>

// ���� :
class Monster : public GameObject
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

//protected:
//	GameEngineImageRenderer* ImageRenderer;

protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);
	virtual void ReleaseEvent();

};

