#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineFSM.h>

class GameEngineImageRenderer;

class WorldMapPlayer : GameEngineActor
{
	friend class WorldMapScene;
	friend class GameEngineLevel;

public:
	WorldMapPlayer(); // default constructer ����Ʈ ������
	~WorldMapPlayer(); // default destructer ����Ʈ �Ҹ���

	WorldMapPlayer(const WorldMapPlayer& _other) = delete; // default Copy constructer ����Ʈ ���������
	WorldMapPlayer(WorldMapPlayer&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	WorldMapPlayer& operator=(const WorldMapPlayer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WorldMapPlayer& operator=(const WorldMapPlayer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:	// member Var
	GameEngineImageRenderer* PlayerImageRenderer;
	GameEngineCollision* PlayerCollision;
	GameEngineFSM<WorldMapPlayer> State_;



	bool KeyState_Up_;
	bool KeyState_Down_;
	bool KeyState_Left_;
	bool KeyState_Right_;


	bool ColState_;



private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private: //Setting
	void KeySetting();
	void StateSetting();
	void ComponentSetting();
	void AnimationSetting();

private:
	StateInfo Idle_Start(StateInfo _state);
	StateInfo Idle_Update(StateInfo _state, float _DeltaTime);
	void Idle_End();

	StateInfo Walk_Start(StateInfo _state);
	StateInfo Walk_Update(StateInfo _state, float _DeltaTime);
	void Walk_End();

	StateInfo Chose_Start(StateInfo _state);
	StateInfo Chose_Update(StateInfo _state, float _DeltaTime);
	void Chose_End();

public:
};

