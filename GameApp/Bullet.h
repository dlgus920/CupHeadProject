#pragma once
#include <GameEngineBase/GameEngineFSM.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>

// 설명 :
class GameEngineImageRenderer;

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
	GameEngineCollision* BulletHitBox_;
	float4 MoveDir_;

protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);
	virtual void ReleaseEvent();

protected:
	void BulletRotate(float4 _Rot);
	void BulletMove(float4 _Pos);
	void BulletScale(float _x, float _y);
	void BulletSort(float _Zorder);

protected:

	template<typename EffectType>
	void BulletCollisionSpawnEffect(CollisionGruop _CollisionGruop)
	{
		EffectType* Effect = GetLevel()->CreateActor<EffectType>();

		Death();
	}

	//const bool BulletCollisionCheck(CollisionGruop _CollisionGruop)
	//{
	//	return BulletHitBox_->Collision(static_cast<int>(_CollisionGruop));
	//}

	void SetMoveDir(float4 _MoveDir)
	{
		MoveDir_ = _MoveDir;
	}
};

class Bullet_Defalut : public GameEngineActor
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

private:
	GameEngineImageRenderer* ImageRenderer_;
	float4 MoveDir_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetMoveDir(float4 _MoveDir)
	{
		MoveDir_ = _MoveDir;
	}
};

class Bullet_Spread : public Bullet
{
public:
	// constrcuter destructer
	Bullet_Spread();
	~Bullet_Spread();
	// 후에 복사생성을 고려해서 디자인 할것
	Bullet_Spread(const Bullet_Spread& _Other) = delete;
	Bullet_Spread(Bullet_Spread&& _Other) = delete;
	Bullet_Spread& operator=(const Bullet_Spread& _Other) = delete;
	Bullet_Spread& operator=(Bullet_Spread&& _Other) = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
};

class Bullet_Guided : public Bullet
{
public:
	// constrcuter destructer
	Bullet_Guided();
	~Bullet_Guided();
	// 후에 복사생성을 고려해서 디자인 할것
	Bullet_Guided(const Bullet_Guided& _Other) = delete;
	Bullet_Guided(Bullet_Guided&& _Other) = delete;
	Bullet_Guided& operator=(const Bullet_Guided& _Other) = delete;
	Bullet_Guided& operator=(Bullet_Guided&& _Other) = delete;

private:

	//주변적을 찾아서 탐색, 
	GameEngineActor* Target_;

	float4 OriginDir_;
	float4 TargetDir_;

	float OriginSpeed_;
	float TargetSpeed_;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
};