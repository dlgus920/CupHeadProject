#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"
#include "Enums.h"

// 이녀석들만의 그룹을 만들겠습니다.


// 설명 :
class GameEngineCore;
class GameEngineLevel;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineCore;
	friend GameEngineLevel;

public:
	GameEngineCollision();
	~GameEngineCollision();

	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) = delete;

public:
	CollisionType CollisionType_;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	GameEngineCollision* CollisionPtr(int _OtherGroup);
	bool Collision(int _OtherGroup);

public:
	void SetCollisionGroup(int _Type);

	template<typename UserType>
	void SetCollisionGroup(UserType _Type)
	{
		SetCollisionGroup(static_cast<int>(_Type));
	}

	void SetCollisionType(CollisionType _CollisionType)
	{
		CollisionType_ = _CollisionType;
	}

private:
	static std::function<bool(GameEngineTransform*, GameEngineTransform*)>
		CollisionCheckFunction[static_cast<int>(CollisionType::MAX)][static_cast<int>(CollisionType::MAX)];

private:
	static void Init();

public:
	static bool CirCleToCirCle(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool RectToRect(GameEngineTransform* _Left, GameEngineTransform* _Right);

	static bool RectToCirCle(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool CirCleToRect(GameEngineTransform* _Left, GameEngineTransform* _Right);
};

