#include "PreCompile.h"
#include "Player.h"
#include "Map.h"
#include "Image.h"
#include "GameEngine/GameEngineCollision.h"

void Player::Update(float _DeltaTime)
{
	//GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);  //디버그 렌더러 생성

	//GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	if (true == KeyState_Update_)
	{
		KeyUpdate();
	}

	if (true == ColState_Update_) // 정교화를 위해 호출시점을 바꿀 필요가 있음
	{
		CollisonUpdate(); // 컬리젼 업데이트에서 상대방과 충돌 여부를 검사하고, stateupdate에서ㅏ 참고하도록 한다.
		GroundCollisonUpdate();
		ParryCollisonUpdate();
		HitCollisonUpdate();
	}
	if (true == State_Update_)
	{
		StateUpdate(_DeltaTime);
	}

	ImageScaleUpdate();

	//GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect);

	//State_Update_는 State_.Update중에 설정함


}

void Player::StateUpdate(float _DeltaTime)
{
	State_.Update(_DeltaTime);
}

void Player::KeyUpdate()
{
	KeyState_Left_ = GameEngineInput::GetInst().Press("MoveLeft");
	KeyState_Right_ = GameEngineInput::GetInst().Press("MoveRight");
	KeyState_Up_ = GameEngineInput::GetInst().Press("MoveUp");
	KeyState_Down_ = GameEngineInput::GetInst().Press("MoveDown");
	KeyState_Shoot_ = GameEngineInput::GetInst().Press("Fire");
	KeyState_RockOn_ = GameEngineInput::GetInst().Press("RockOn");
	KeyState_Jump_ = GameEngineInput::GetInst().Press("Jump");
	//KeyState_Bomb = GameEngineInput::GetInst().Press("Bomb");
	KeyState_Dash_ = GameEngineInput::GetInst().Press("Dash");

	if (KeyState_Left_ && !KeyState_Right_)
	{
		if (Dir_ == AnimationDirection::Right)
		{
			GetTransform()->SetHorizenInvertTransform();
			//BulletPoint_->GetTransform()->SetLocalPosition(float4{ -50.f,-75.f,static_cast<int>(ZOrder::Z00Fx00) });
		}
		Dir_ = AnimationDirection::Left;
	}

	else if (KeyState_Right_ && !KeyState_Left_)
	{
		if (Dir_ == AnimationDirection::Left)
		{
			GetTransform()->SetHorizenInvertTransform();
			//BulletPoint_->GetTransform()->SetLocalPosition(float4{ 50.f,-75.f,static_cast<int>(ZOrder::Z00Fx00) });
		}
		Dir_ = AnimationDirection::Right;
	}

}

void Player::CollisonUpdate()
{
	ColState_Hit_ = PlayerHitBox->Collision(static_cast<int>(CollisionGruop::Bullet));

	ColState_Parry_ = PlayerHitBox->Collision(static_cast<int>(CollisionGruop::Parry));
}

const bool Player::GroundCollisonUpdate()
{
	ColState_Ground = Map::PixelCollisionTransform(PlayerCollision, 10).b_Down;

	return ColState_Ground;
}

const bool Player::ParryCollisonUpdate()
{
	ColState_Parry_ = PlayerHitBox->Collision(static_cast<int>(CollisionGruop::Parry));

	return ColState_Parry_;
}

const bool Player::HitCollisonUpdate()
{
	ColState_Hit_ = PlayerHitBox->Collision(static_cast<int>(CollisionGruop::Bullet));

	return ColState_Hit_;
}

void Player::ImageScaleUpdate() //아직 미사용
{
	float4 size = PlayerImageRenderer->GetImageSize();

	if (PrevAniSize_ != size)
	{
		PrevAniSize_ = size;

		PlayerImageRenderer->GetTransform()->SetLocalScaling(size);
		PlayerCollision->GetTransform()->SetLocalScaling(size);
		PlayerHitBox->GetTransform()->SetLocalScaling(size);
	}

}

