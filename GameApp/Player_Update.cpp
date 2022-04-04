#include "PreCompile.h"
#include "Player.h"
#include "Map.h"
#include "Image.h"
#include "GameEngine/GameEngineCollision.h"

void Player::Update(float _DeltaTime)
{
	if (true == KeyState_Update_)
	{
		KeyUpdate();
	}

	if (true == State_Update_)
	{
		StateUpdate(_DeltaTime);
	}
}

void Player::StateUpdate(float _DeltaTime)
{
	State_.Update(_DeltaTime);
}

void Player::KeyUpdate()
{
	KeyState_Left_ = GameEngineInput::GetInst().Press("MoveLeft");
	KeyState_Right_ = GameEngineInput::GetInst().Press("MoveRight");
	KeyState_Shoot_ = GameEngineInput::GetInst().Down("Fire");
	KeyState_Shoot2_ = GameEngineInput::GetInst().Press("Fire2");

	//if (KeyState_Left_ && !KeyState_Right_)
	//{
	//	Dir_ = AnimationDirection::Left;
	//}


}

void Player::CollisonUpdate()
{
}

void Player::ImageScaleUpdate() //아직 미사용
{
}

