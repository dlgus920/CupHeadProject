#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// ���� :
class GameEngineComponent;
class GameEngineTransformComponent;
class GameEngineLevel;
class GameEngineTransform;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

public:

	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	bool IsDestroyed_;
	float DeathTime_;

	GameEngineLevel* GetLevel() 
	{
		return Level_;
	}

	void Release(float _Time = 0.0f)
	{
		if (0.0f >= _Time)
		{
			Death();
		}
		else 
		{
			IsDestroyed_ = true;
			DeathTime_ = _Time;
		}
	}

	template<typename ComponentType>
	ComponentType* CreateComponent(int _Order = 0)
	{
		GameEngineComponent* NewComponent = new ComponentType(); 
		NewComponent->SetParent(this);
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		ComponentList_.push_back(NewComponent);
		NewComponent->Start();
		return dynamic_cast<ComponentType*>(NewComponent);;
	}

	template<typename ComponentType>
	ComponentType* CreateTransformComponent(GameEngineTransform* _ParentTrans, int _Order = 0)
	{
		// ��ĳ������ �̿��ؼ� ������ ������ �����̴�.
		GameEngineTransformComponent* NewComponent = new ComponentType();
		NewComponent->SetParent(this);
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		if (nullptr == _ParentTrans)
		{
			GameEngineDebug::MsgBoxError("Ʈ�������� ���þ� ������ϴ�.");
		}
		NewComponent->AttachTransform(_ParentTrans);
		ComponentList_.push_back(NewComponent);

		NewComponent->Start();
		return dynamic_cast<ComponentType*>(NewComponent);;
	}

protected:
	virtual void Start() {}
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime) {}
	virtual void ReleaseEvent() {}

	// Ʈ�������� ��ȭ��Ų�ٴ°� �⺻������ �����Ұ̴ϴ�.

////////////////////////

public:
	GameEngineTransform* GetTransform() 
	{
		return 	Transform_;
	}

private:
	GameEngineTransform* Transform_;
	GameEngineLevel* Level_;

	// Status
	std::list<GameEngineComponent*> ComponentList_;

	std::list<GameEngineTransformComponent*> TransformComponentList_;

	void SetLevel(GameEngineLevel* Level);

	void UpdateComponent();

	void ComponentRelease();

	void ReleaseUpdate(float _DeltaTime);
};

