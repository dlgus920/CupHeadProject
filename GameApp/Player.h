#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineFSM.h>
#include "Bullet.h"
#include "PositionComponent.h"

class GameEngineImageRenderer;

enum class AnimationDirection
{
	Right,
	Left
};

enum class ShootingDir
{	
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

	PositionComponent* BulletPoint_;
	PositionComponent* BulletPointOrigin_;

	GameEngineFSM<Player> State_;

	GameEngineTransform* Camera_;

	GameEngineCollision* PlayerHitBox;
	GameEngineCollision* PlayerMovingCollision;
	GameEngineCollision* PlayerCollision;

	float4 PrevAniSize_;

	float TimeCheck_;
	float DistTimeCheck_;

	float ShootingInterTime_;

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
	
	//무적시간 판별 여부
	bool  HitInvince_;
	float HitInvinceTime_;

	// 현재 보고 있는 방향
	BulletType BulletType_;
	BulletInfo BulletInfo_;

	//float4 ShootingDir_;

	float4 ShootingPos_[10];

	AnimationDirection		Dir_; // 보고있는 왼쪽, 오른쪽 방향
	ShootingDir				ShootingDir_; // 현재 누르고 있는 키 방향 (대각선포함)

	//float4 MoveDir_;

	std::string CurState_;

	std::function<void()> BulletShootFunc_;

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private://Func
	void ChangeAnimation(std::string _animation);
	StateInfo ChangeState();
	const std::string CheckState();

	void Move(float4 MoveDir, float _DeltaTime); // Cold 하게 무브만 함
	void Move(float DirX, float DirY, float _DeltaTime);
	
	//const bool MapCollisionMove(float4 _MoveDist, float _DeltaTime);
	//const bool MapCollisionMove(float DirX, float DirY, float _DeltaTime); 
	// 10픽셀 차이로 맵의 곡선을 넘을 수 있나 체크하고 이동함(못하면 안함), 근데 이거 필요한가? 컵헤드 곡선맵 있나?, 월드맵에서?

	void ChangeShootFunc(void(Player::* _FrameFunc)());

	void ShootGuidedBullet();
	void ShootSpreadBullet();
	void ShootDefalutBullet();

	float4 GetBulletPoint();

	void GravityUpdate(float _DeltaTime);
	void GravityClear();

	void CheckShootDir();

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
	void Bomb_Start();
	StateInfo Bomb_Update(StateInfo _state, float _DeltaTime);
	void Bomb_End();

	void Death_Start();
	StateInfo Death_Update(StateInfo _state, float _DeltaTime);
	void Death_End();

	void Dash_Start();
	StateInfo Dash_Update(StateInfo _state, float _DeltaTime);
	void Dash_End();

	void Jump_Start();
	StateInfo Jump_Update(StateInfo _state, float _DeltaTime);
	void Jump_End();

	void Idle_Start();
	StateInfo Idle_Update(StateInfo _state, float _DeltaTime);
	void Idle_End();

	void Walk_Start();
	StateInfo Walk_Update(StateInfo _state, float _DeltaTime);
	void Walk_End();

	void Duck_Start();
	StateInfo Duck_Update(StateInfo _state, float _DeltaTime);
	void Duck_End();

	void RockOn_Start();
	StateInfo RockOn_Update(StateInfo _state, float _DeltaTime);
	void RockOn_End();

	void Hit_Start();
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

