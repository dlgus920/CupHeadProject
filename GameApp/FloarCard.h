#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

class FloarCard : public GameEngineActor
{
public:
	FloarCard();
	~FloarCard();

	FloarCard(const FloarCard& _other) = delete;
	FloarCard(FloarCard&& _other) = delete;
	FloarCard& operator=(const FloarCard& _other) = delete;
	FloarCard& operator=(const FloarCard&& _other) = delete;

private:
	class GameEngineImageRenderer* ImageRenderer;
	class GameEngineCollision* Collision;
	class GameEngineCollision* Collisiondummy;

private:	
	void Start() override;
	void Update(float _DeltaTime) override;
};

