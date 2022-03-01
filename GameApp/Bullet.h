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


protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);
	virtual void ReleaseEvent();

public:
	void SetMoveDir(float4 _MoveDir)
	{
		MoveDir_ = _MoveDir;
	}
};

