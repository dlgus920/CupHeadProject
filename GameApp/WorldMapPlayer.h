#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineFSM.h>

class GameEngineImageRenderer;

enum class AnimationDirection
{
	Right,
	Left,
};

class WorldMapPlayer : public GameEngineActor
{
	friend class WorldMapScene;
	friend class GameEngineLevel;

private:
	WorldMapPlayer(); // default constructer ����Ʈ ������
	~WorldMapPlayer(); // default destructer ����Ʈ �Ҹ���

	WorldMapPlayer(const WorldMapPlayer& _other) = delete; // default Copy constructer ����Ʈ ���������
	WorldMapPlayer(WorldMapPlayer&& _other) noexcept  = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	WorldMapPlayer& operator=(const WorldMapPlayer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WorldMapPlayer& operator=(const WorldMapPlayer&& _other) noexcept  = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:	// member Var
	GameEngineImageRenderer* PlayerImageRenderer;
	GameEngineCollision* PlayerCollision;
	GameEngineFSM<WorldMapPlayer> State_;

	float4 MoveDir_;

	std::string CurState_;

	bool KeyState_Update_;
	bool ColState_Update_;
	bool State_Update_;

	bool KeyState_Up_;
	bool KeyState_Down_;
	bool KeyState_Left_;
	bool KeyState_Right_;

	bool KeyState_Chose_;


	bool ColState_;


	AnimationDirection		Dir_; // �����ִ� ����, ������ ����

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private: //Setting
	void KeySetting();
	void StateSetting();
	void ComponentSetting();
	void AnimationSetting();

private: //Update
	void StateUpdate(float _DeltaTime);
	void KeyUpdate();
	void CollisonUpdate();

private: // Func

	std::string CheckState();
	void Move(float4 MoveDir, float _DeltaTime);
	void Move(float DirX, float DirY, float _DeltaTime);

	void SetChangeAnimation(std::string _animation);

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
};

