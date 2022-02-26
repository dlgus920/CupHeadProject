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

	GameEngineFSM<Player> State_;

	//누르고 있는가
	bool Key_Up_;
	bool Key_Down_;
	bool Key_Left_;
	bool Key_Right_;

	bool Key_Shoot_;

	bool Key_RockOn_;
	bool Key_Bomb;
	bool Key_Jump_;

	bool Key_Hit_;
	bool Key_Dash_;

	// state
	bool State_Ground;
	bool State_Hit_;
	// 현재 보고 있는 방향
	Dir		Dir_; // 보고있는 왼쪽, 오른쪽 방향
	KeyDir	KeyDir_; // 현재 누르고 있는 키 방향 (대각선포함)

	float4 MoveDir_;

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private: //Setting
	void KeySetting();
	void StateSetting();
	void RendererSetting();
	void TransformSetting();

private: //Update
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
	StateInfo Idle_Start(StateInfo _state);
	StateInfo Idle_Update(StateInfo _state, float _DeltaTime);

	StateInfo Walk_Start(StateInfo _state);
	StateInfo Walk_Update(StateInfo _state, float _DeltaTime);

	StateInfo Jump_Start(StateInfo _state);
	StateInfo Jump_Update(StateInfo _state, float _DeltaTime);

	StateInfo Duck_Start(StateInfo _state);
	StateInfo Duck_Update(StateInfo _state, float _DeltaTime);
	//StateInfo Shoot_Start(StateInfo _state);
	//StateInfo Shoot_Update(StateInfo _state, float _DeltaTime);

	StateInfo RockOn_Start(StateInfo _state);
	StateInfo RockOn_Update(StateInfo _state, float _DeltaTime);

	StateInfo Bomb_Start(StateInfo _state);
	StateInfo Bomb_Update(StateInfo _state, float _DeltaTime);

	StateInfo Death_Start(StateInfo _state);
	StateInfo Death_Update(StateInfo _state, float _DeltaTime);

	StateInfo Hit_Start(StateInfo _state);
	StateInfo Hit_Update(StateInfo _state, float _DeltaTime);

	StateInfo Dash_Start(StateInfo _state);
	StateInfo Dash_Update(StateInfo _state, float _DeltaTime);

public: //Inline
	std::string GetCurState()
	{
		return State_.GetName();
	}

};

