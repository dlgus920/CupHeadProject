#pragma once
#include <GameEngineBase/GameEngineFSM.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>

// 설명 :
class GameEngineImageRenderer;

struct BulletInfo
{
	BulletInfo()
		: BulletSpeed_(0.f)
		, MoveDir_(float4::ZERO)
		, BulletDamage_(0)
	{}
	BulletInfo(float4 _MoveDIr, float _BulletSpeed, int _BulletDamage)
	{
		MoveDir_ = _MoveDIr;
		BulletSpeed_ = _BulletSpeed;
		BulletDamage_ = _BulletDamage;
	}

	float4 MoveDir_;
	float BulletSpeed_;
	int BulletDamage_;
};

class Bullet : public GameEngineActor
{
	friend class Player;
	friend class PlayLevel;
public:
	// constrcuter destructer
	Bullet();
	~Bullet();
	// 후에 복사생성을 고려해서 디자인 할것
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) = delete;

protected:
	GameEngineImageRenderer* BulletRenderer_;
	GameEngineCollision* BulletCollision_;

	BulletInfo BulletInfo_;
	float BulletLifeTile_;

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);

protected:
	void SetBulletInfo(BulletInfo _BulletInfo);
};

class Bullet_Defalut : public Bullet
{
public:
	// constrcuter destructer
	Bullet_Defalut();
	~Bullet_Defalut();
	// 후에 복사생성을 고려해서 디자인 할것
	Bullet_Defalut(const Bullet_Defalut& _Other) = delete;
	Bullet_Defalut(Bullet_Defalut&& _Other) = delete;
	Bullet_Defalut& operator=(const Bullet_Defalut& _Other) = delete;
	Bullet_Defalut& operator=(Bullet_Defalut&& _Other) = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void BulletDeath();
};
