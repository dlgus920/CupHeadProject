#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineFSM.h>

// 설명 :
class GameEngineImageRenderer;

enum class Dir
{
	Right,
	Left
};

enum class AnimationOnfo
{
	Idle_Right,
	Idle_Left,
	Duck_Right_Idle,
	Duck_Left_Idle,
	Duck_Right_Shoot,
	Duck_Left_Shoot,
	Death_Right,
	Death_Left,
	Dash,
	Rockon,
	Walk,
	Shoot,
	Hit,
	Jump,
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
	GameEngineTransform* Camera_;

	// state
	bool State_Update_;

	bool KetState_Up_;
	bool KetState_Down_;
	bool KetState_Left_;
	bool KetState_Right_;

	bool KetState_Shoot_;

	bool KetState_RockOn_;
	bool KetState_Bomb;
	bool KetState_Jump_;

	bool KetState_Hit_;
	bool KetState_Dash_;

	bool ColState_Ground;
	bool ColState_Hit_;

	// 현재 보고 있는 방향
	Dir		Dir_; // 보고있는 왼쪽, 오른쪽 방향
	KeyDir	KeyDir_; // 현재 누르고 있는 키 방향 (대각선포함)

	float4 MoveDir_;

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private: //Setting
	void ComponentSetting();
	void KeySetting();
	void StateSetting();
	void RendererSetting();
	void TransformSetting();
	void CollisionSetting();

private: //Update
	void KeyStateUpdate(float _DeltaTime);
	void StateUpdate(float _DeltaTime);
	void KeyUpdate(float _DeltaTime);
	void CollisonUpdate();
	void GravityUpdate(float _DeltaTime);
private://Func

	void Shoot(float4 ShootDir);
	void Shoot(float ShootDirX, float ShootDirY);
	void Move(float4 MoveDir, float _DeltaTime);
	void Move(float DirX, float DirY, float _DeltaTime);
		
private: //State_
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

