#include "PreCompile.h"
#include "Player.h"
#include "Map.h"
#include "GameEngine/GameEngineCollision.h"


void Player::StateUpdate(float _DeltaTime)
{
	State_Update_ = true;
}

void Player::KeyUpdate(float _DeltaTime)
{
	KeyState_Left_ = GameEngineInput::GetInst().Down("MoveLeft");
	KeyState_Right_ = GameEngineInput::GetInst().Down("MoveRight");

	if (KeyState_Left_ && !KeyState_Right_)
	{
		if (Dir_ == AnimationDirection::Left)
			GetTransform()->SetHorizenInvertTransform();
		Dir_ = AnimationDirection::Right;
	}

	else if (KeyState_Right_ && !KeyState_Left_)
	{
		if (Dir_ == AnimationDirection::Right)
			GetTransform()->SetHorizenInvertTransform();
		Dir_ = AnimationDirection::Left;
	}

	KeyState_Up_ = GameEngineInput::GetInst().Down("MoveUp");
	KeyState_Down_ = GameEngineInput::GetInst().Down("MoveDown");

	KeyState_Shoot_ = GameEngineInput::GetInst().Down("Fire");

	KeyState_Bomb = GameEngineInput::GetInst().Down("Bomb");
	KeyState_Jump_ = GameEngineInput::GetInst().Down("Jump");
	KeyState_Dash_ = GameEngineInput::GetInst().Down("Dash");
	KeyState_RockOn_ = GameEngineInput::GetInst().Down("RockOn");
}

void Player::CollisonUpdate()
{
	if (PlayerHitBox->Collision(static_cast<int>(CollisionGruop::Bullet)))
	{
		ColState_Hit_ = true;
	}

	float4 Color = Map::GetColor(GetTransform());

	if (Color != float4::BLACK)
	{
		ColState_Ground = true;
	}

	else
	{
		ColState_Ground = false;
	}
}

void Player::GravityUpdate(float _DeltaTime)
{
	GetTransform()->SetLocalMove(float4::DOWN * _DeltaTime);
}

