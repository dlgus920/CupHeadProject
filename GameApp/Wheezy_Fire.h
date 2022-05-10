#pragma once
#include <GameEngineBase/GameEngineFSM.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>
class Mr_Wheezy;

class Wheezy_Fire : public GameEngineActor
{
	friend class Mr_Wheezy;
	friend class GameEngineLevel;
private:
	Wheezy_Fire();
	~Wheezy_Fire();

	Wheezy_Fire(const Wheezy_Fire& _other) = delete;
	Wheezy_Fire(Wheezy_Fire&& _other) = delete;
	Wheezy_Fire& operator=(const Wheezy_Fire& _other) = delete;
	Wheezy_Fire& operator=(const Wheezy_Fire&& _other) = delete;

public:
	class RotCore : public GameEngineTransformComponent
	{
		friend Wheezy_Fire;
		friend GameEngineActor;

		RotCore()
		{
		}
		~RotCore()
		{
		}
		void Start() {}
		void Update(float _DeltaTime) {}
		void ReleaseEvent() {}
		void LevelChangeEndEvent(GameEngineLevel* _NextLevel) {}
		void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) {}

		// delete Function
		RotCore(const RotCore& _Other) = delete;
		RotCore(RotCore&& _Other) noexcept = delete;
		RotCore& operator=(const RotCore& _Other) = delete;
		RotCore& operator=(RotCore&& _Other) = delete;
	};

private:
	GameEngineCollision* FireHitBox_;
	GameEngineImageRenderer* FireImageRenderer_;
	RotCore* Component_;
	RotCore* ComponentChild_;

	float fRotValue_;
	float fDirValue_;
	float TimeCheck_;
	float DeathTimeCheck_;

private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetDir(bool Right)
	{
		if (true == Right)
		{
			fDirValue_ = 150.f;
		}
		else
		{
			fDirValue_ = -150.f;
		}
	}

};

