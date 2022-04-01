#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineFSM.h>
#include "Bullet.h"

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

enum class BulletType
{
	Default,
	Guided,
	Spread
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

	GameEngineTransform* BulletPoint_;

	GameEngineFSM<Player> State_;
	//GameEngineFSM<Player> AnimationState_;

	GameEngineTransform* Camera_;

	GameEngineCollision* PlayerHitBox;
	GameEngineCollision* PlayerMovingCollision;
	GameEngineCollision* PlayerCollision;

	float4 PrevAniSize_;

	float TimeCheck_;
	float DistTimeCheck_;

	float GravitySpeed_;
	float GravityAcc_;

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
	
	//�����ð� �Ǻ� ����
	bool  HitInvince_;
	float HitInvinceTime_;

	// ���� ���� �ִ� ����
	BulletType BulletType_;
	AnimationDirection		Dir_; // �����ִ� ����, ������ ����
	KeyDir					KeyDir_; // ���� ������ �ִ� Ű ���� (�밢������)

	//float4 MoveDir_;

	std::string CurState_;

	std::function<void(float4)> BulletShootFunc_;

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private://Func
	void ChangeAnimation(std::string _animation);
	StateInfo ChangeState();
	const std::string CheckState();

	void Move(float4 MoveDir, float _DeltaTime); // Cold �ϰ� ���길 ��
	void Move(float DirX, float DirY, float _DeltaTime);
	
	//const bool MapCollisionMove(float4 _MoveDist, float _DeltaTime);
	//const bool MapCollisionMove(float DirX, float DirY, float _DeltaTime); 
	// 10�ȼ� ���̷� ���� ��� ���� �� �ֳ� üũ�ϰ� �̵���(���ϸ� ����), �ٵ� �̰� �ʿ��Ѱ�? ����� ��� �ֳ�?, ����ʿ���?

	void ChangeShootFunc(void(Player::* _FrameFunc)(float4));

	void ShootGuidedBullet(float4 _Dir);
	void ShootSpreadBullet(float4 _Dir);
	void ShootDefalutBullet(float4 _Dir);

	float4 GetBulletPoint();

	void GravityUpdate(float _DeltaTime);
	void GravityClear();

private: //Setting
	void KeySetting();
	void StateSetting();
	void ComponentSetting();
	void AnimationSetting();

private: //Update
	void StateUpdate(float _DeltaTime);
	void KeyUpdate();
	void CollisonUpdate();
	void ImageScaleUpdate();
		
private: 
#pragma region State_
	StateInfo Bomb_Start(StateInfo _state);
	StateInfo Bomb_Update(StateInfo _state, float _DeltaTime);
	void Bomb_End();

	StateInfo Death_Start(StateInfo _state);
	StateInfo Death_Update(StateInfo _state, float _DeltaTime);
	void Death_End();

	StateInfo Dash_Start(StateInfo _state);
	StateInfo Dash_Update(StateInfo _state, float _DeltaTime);
	void Dash_End();

	StateInfo Jump_Start(StateInfo _state);
	StateInfo Jump_Update(StateInfo _state, float _DeltaTime);
	void Jump_End();

	StateInfo Idle_Start(StateInfo _state);
	StateInfo Idle_Update(StateInfo _state, float _DeltaTime);
	void Idle_End();

	StateInfo Walk_Start(StateInfo _state);
	StateInfo Walk_Update(StateInfo _state, float _DeltaTime);
	void Walk_End();

	StateInfo Duck_Start(StateInfo _state);
	StateInfo Duck_Update(StateInfo _state, float _DeltaTime);
	void Duck_End();

	StateInfo RockOn_Start(StateInfo _state);
	StateInfo RockOn_Update(StateInfo _state, float _DeltaTime);
	void RockOn_End();

	StateInfo Hit_Start(StateInfo _state);
	StateInfo Hit_Update(StateInfo _state, float _DeltaTime);
	void Hit_End();
#pragma endregion


public: //Inline
	void SetStateUpdateOn()
	{
		State_Update_ = true;
	}
	void SetStateUpdateOff()
	{
		State_Update_ = false;
	}

	const std::string GetCurState()
	{
		return State_.GetName();
	}


};

