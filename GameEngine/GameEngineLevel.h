#pragma once
#include <list>
#include <map>
#include <GameEngine\Enums.h>
#include <GameEngineBase\GameEngineObjectNameBase.h>

class CameraActor;
class CameraComponent;
class GameEngineActor;
class GameEngineRenderer;
class GameEngineTransform;
class GameEngineCollision;
class GameEngineDebugRenderData;
class GameEnginePostProcessRender;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;
	friend class GameEngineRenderer;
	friend class GameEngineCollision;
	friend class GameEngineLevelControlWindow;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	CameraActor* GetMainCameraActor();
	CameraComponent* GetMainCamera();

	CameraActor* GetUICameraActor();
	CameraComponent* GetUICamera();
private:
	class NextLevelActor
	{
	public:
		GameEngineActor* Actor;
		GameEngineLevel* Level;
	};

private:

	std::vector<NextLevelActor> NextLevelActorsData_;
	CameraActor* MainCameraActor_;
	CameraActor* UICameraActor_;

	std::map<int, std::list<GameEngineActor*>> ActorList_;	

	std::map<int, std::list<GameEngineCollision*>> CollisionList_;
	bool IsDebug_;

	std::map<std::string, std::vector<GameEnginePostProcessRender*>> PostRender;

public:

	void ActorUpdate(float _DeltaTime);
	void Render(float _DeltaTime);
	void Release(float _DeltaTime);

	void AllClear(); 

	void PushDebugRender(GameEngineTransform* _Transform, CollisionType _Type, float4 _Color = float4::RED);

	void PushCollision(GameEngineCollision* _Collision, int _Group);
	
	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) = 0;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) = 0;

	void SetLevelActorMove(GameEngineLevel* _NextLevel, GameEngineActor* _Actor);


private:
	void Init();

	void ChangeCollisionGroup(int _Group, GameEngineCollision* _Collision);
	void LevelChangeEndActorEvent(GameEngineLevel* _NextLevel);
	void LevelChangeStartActorEvent(GameEngineLevel* _PrevLevel);

	void SetLevelActorMoveProcess();

	inline std::list<GameEngineCollision*>& GetCollisionGroup(int _Group)
	{
		return CollisionList_[_Group];
	}

public:

	void SetDebug(bool _Debug)
	{
		IsDebug_ = _Debug;
	}

public:

	template<typename ActorType>
	ActorType* CreateActor(int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->SetLevel(this);
		NewActor->Start();
		NewActor->SetOrder(_UpdateOrder);

		// Insert + Find
		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	template<typename UserEnumType>
	void PushCollision(GameEngineCollision* _Collision, UserEnumType _Group)
	{
		PushCollision(_Collision, static_cast<int>(_Group));
	}

	template<typename PostProcess, typename ... Parameter>
	PostProcess* AddPostProcessCameraMergePrev(Parameter ... _Arg)
	{
		return AddPostProcess<PostProcess>("CameraMergePrev", _Arg...);
	}

	template<typename PostProcess, typename ... Parameter >
	PostProcess* AddPostProcessCameraMergeNext(Parameter ... _Arg)
	{
		return AddPostProcess<PostProcess>("CameraMergeNext", _Arg...);
	}

	template<typename PostProcess, typename ... Parameter >
	PostProcess* AddPostProcess(const std::string& _Key, Parameter ... _Arg)
	{
		PostProcess* NewPost = new PostProcess(_Arg...);
		GameEnginePostProcessRender* ParentType = dynamic_cast<GameEnginePostProcessRender*>(NewPost);
		ParentType->Initialize();
		PostRender[_Key].push_back(NewPost);
		return NewPost;
	}
};