#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineCollision;
class GameEngineImageRenderer;
class Hopus_Bullet : public GameEngineActor
{
public:
	Hopus_Bullet();
	~Hopus_Bullet();

	Hopus_Bullet(const Hopus_Bullet& _other) = delete;
	Hopus_Bullet(Hopus_Bullet&& _other) = delete;
	Hopus_Bullet& operator=(const Hopus_Bullet& _other) = delete;
	Hopus_Bullet& operator=(const Hopus_Bullet&& _other) = delete;

private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineImageRenderer* FireImageRenderer[8];
	GameEngineCollision* FireCollision[8];

	float Dist_;
	bool Roll_;
	float TimeCheck_;

public:
	void Reset();
};

