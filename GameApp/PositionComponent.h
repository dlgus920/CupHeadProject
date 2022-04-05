#pragma once
#include "GameEngine/GameEngineTransformComponent.h"


class PositionComponent : public GameEngineTransformComponent
{
	friend class GameEngineCore;
	friend class GameEngineLevel;
	friend class GameEngineActor;

public:
	PositionComponent(); // default constructer 디폴트 생성자
	~PositionComponent(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	PositionComponent(const PositionComponent& _other) = delete; 
	PositionComponent(PositionComponent&& _other) = delete; 
	PositionComponent& operator=(const PositionComponent& _other) = delete; 
	PositionComponent& operator=(const PositionComponent&& _other) = delete; 

private:	// member Var


private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:


};

