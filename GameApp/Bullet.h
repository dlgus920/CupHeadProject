#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

private:
	float4 MoveDir_;


private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetMoveDir(float4 _MoveDir)
	{
		MoveDir_ = _MoveDir;
	}
};

