#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineFSM.h>

class GameEngineImageRenderer;

enum class AnimationDirection
{
	Right,
	Left
};

enum class KeyDir
{	
	None,
	Right,
	Right_Up,
	Right_Down,
	Left,
	Left_Up,
	Left_Down,
	Up_Left,
	Up_Right,
	Down_Left,
	Down_Right,
};

class Player : public GameEngineActor
{
	friend class PlayLevel;
	friend class GameEngineLevel;

private:
	Player();
	~Player();
	 //delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

private: //Member
	GameEngineImageRenderer* PlayerImageRenderer;

	GameEngineTransformComponent* BulletPoint_;

	GameEngineFSM<Player> State_;
	GameEngineFSM<Player> AnimationState_;
	GameEngineTransform* Camera_;

		// state
	bool KeyState_Update_;
	bool ColState_Update_;
	bool State_Update_;

	bool KeyState_Up_;
	bool KeyState_Down_;
	bool KeyState_Left_;
	bool KeyState_Right_;

	bool KeyState_Shoot_;

	bool KeyState_RockOn_;
	bool KeyState_Bomb;
	bool KeyState_Jump_;

	bool KeyState_Hit_;
	bool KeyState_Dash_;

	bool ColState_Ground;
	bool ColState_Hit_;
	

	// 현재 보고 있는 방향
	AnimationDirection		Dir_; // 보고있는 왼쪽, 오른쪽 방향
	KeyDir					KeyDir_; // 현재 누르고 있는 키 방향 (대각선포함)

	float4 MoveDir_;

	GameEngineCollision* PlayerHitBox;
	GameEngineCollision* PlayerMovingCollision;
	GameEngineCollision* PlayerCollision;

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private://Func
	void ChangeAnimation(std::string _animation);
	void ChangeAnimation();
	void ChangeState();
	void Shoot(float4 ShootDir);
	void Shoot(float ShootDirX, float ShootDirY);
	void Move(float4 MoveDir, float _DeltaTime);
	void Move(float DirX, float DirY, float _DeltaTime);

private: //Setting
	void ComponentSetting();
	void KeySetting();
	void StateSetting();
	void RendererSetting();
	void AnimationSetting();
	void TransformSetting();
	void CollisionSetting();

private: //Update
	void KeyStateUpdate(float _DeltaTime);
	void StateUpdate(float _DeltaTime);
	void KeyUpdate(float _DeltaTime);
	void CollisonUpdate();
	void GravityUpdate(float _DeltaTime);
		
private: 
#pragma region State_
	StateInfo Bomb_Start(StateInfo _state);
	StateInfo Bomb_Update(StateInfo _state, float _DeltaTime);

	StateInfo Death_Start(StateInfo _state);
	StateInfo Death_Update(StateInfo _state, float _DeltaTime);

	StateInfo Dash_Start(StateInfo _state);
	StateInfo Dash_Update(StateInfo _state, float _DeltaTime);

	StateInfo Jump_Start(StateInfo _state);
	StateInfo Jump_Update(StateInfo _state, float _DeltaTime);


	StateInfo Idle_Start(StateInfo _state);
	StateInfo Idle_Update(StateInfo _state, float _DeltaTime);

	StateInfo Walk_Start(StateInfo _state);
	StateInfo Walk_Update(StateInfo _state, float _DeltaTime);

	StateInfo Duck_Start(StateInfo _state);
	StateInfo Duck_Update(StateInfo _state, float _DeltaTime);
	//StateInfo Shoot_Start(StateInfo _state);
	//StateInfo Shoot_Update(StateInfo _state, float _DeltaTime);

	StateInfo RockOn_Start(StateInfo _state);
	StateInfo RockOn_Update(StateInfo _state, float _DeltaTime);

	StateInfo Hit_Start(StateInfo _state);
	StateInfo Hit_Update(StateInfo _state, float _DeltaTime);
#pragma endregion

#pragma region AnimationState

	StateInfo AnimationReady_Start(StateInfo _state); // 현재 state에 맞는 키가 눌려있지 않으면 그에 맞게 에니메이션을 바꿈
	StateInfo AnimationReady_Update(StateInfo _state, float _DeltaTime);

	StateInfo Animation_Idle_Start(StateInfo _state);
	StateInfo Animation_Idle_Update(StateInfo _state, float _DeltaTime);

	StateInfo Animation_Walk_Start(StateInfo _state);
	StateInfo Animation_Walk_Update(StateInfo _state, float _DeltaTime);

	StateInfo Animation_Shoot_Start(StateInfo _state);
	StateInfo Animation_Shoot_Update(StateInfo _state, float _DeltaTime);

	StateInfo Animation_Duck_Start(StateInfo _state);
	StateInfo Animation_Duck_Update(StateInfo _state, float _DeltaTime);

	StateInfo _Start(StateInfo _state);
	StateInfo _Update(StateInfo _state, float _DeltaTime);
#pragma endregion
	//필요할때 딱 한번만 실행됨
	//에니메이션 별로 state를 만들까 계획중



public: //Inline
	void SetStateUpdateOn()
	{
		State_Update_ = true;
	}
	void SetStateUpdateOff()
	{
		State_Update_ = false;
	}

	std::string GetCurState()
	{
		return State_.GetName();
	}


};

