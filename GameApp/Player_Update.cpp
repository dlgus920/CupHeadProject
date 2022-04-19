#include "PreCompile.h"
#include "Player.h"
#include "Map.h"
#include "Image.h"
#include "GameEngine/GameEngineCollision.h"

#ifdef _DEBUG
void Player::Update_DEBUG()
{
	GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect);

	if (PlayerParryCollision->Collision(static_cast<int>(CollisionGruop::Parry)))
	{
		GetLevel()->PushDebugRender(PlayerParryCollision->GetTransform(), CollisionType::Rect, float4::PINK);
	}
	else
	{
		GetLevel()->PushDebugRender(PlayerParryCollision->GetTransform(), CollisionType::Rect, float4::BLUE);
	}
}
#endif // _DEBUG

void Player::Update(float _DeltaTime)
{
	KeyUpdate();
	GroundCollisonUpdate();
	ParryCollisonUpdate();
	HitCollisonUpdate();
	StateUpdate(_DeltaTime);

	//ImageScaleUpdate();

	//GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect);

	//State_Update_는 State_.Update중에 설정함

	if (true == HitInvince_)
	{
		//반짝임 효과

		HitInvinceTimeCheck_ += _DeltaTime;

		PlayerHitBox->Off();
		//컬리젼 해제

		if (blit_)
		{
			PlayerImageRenderer->SetResultColor(float4{1.f,1.f,1.f,0.6f});
			blit_ = false;
		}
		else
		{
			PlayerImageRenderer->SetResultColor(float4{ 1.f,1.f,1.f,1.f });
			blit_ = true;
		}

		if (HitInvinceTime_ <= HitInvinceTimeCheck_)
		{
			PlayerHitBox->On();
			HitInvince_ = false;
			PlayerImageRenderer->SetResultColor(float4{ 1.f,1.f,1.f,1.f });
			HitInvinceTimeCheck_ = 0.f;
			//반짝임 효과 해제
		}
	}

#ifdef _DEBUG
	Update_DEBUG();
#endif // _DEBUG
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
	KeyState_Jump_ = GameEngineInput::GetInst().Down("Jump");
	KeyState_Jump_Press = GameEngineInput::GetInst().Press("Jump");
	//KeyState_Bomb = GameEngineInput::GetInst().Press("Bomb");
	KeyState_Dash_ = GameEngineInput::GetInst().Press("Dash");

	if (KeyState_Left_ && !KeyState_Right_)
	{
		if (Dir_ == AnimationDirection::Right)
		{
			PlayerImageRenderer->GetTransform()->SetHorizenInvertTransform();
			WalkState_Changed_ = true;
			//BulletPoint_->GetTransform()->SetLocalPosition(float4{ -50.f,-75.f,static_cast<int>(ZOrder::Z00Fx00) });
		}
		Dir_ = AnimationDirection::Left;
	}

	else if (KeyState_Right_ && !KeyState_Left_)
	{
		if (Dir_ == AnimationDirection::Left)
		{
			PlayerImageRenderer->GetTransform()->SetHorizenInvertTransform();
			WalkState_Changed_ = true;
			//BulletPoint_->GetTransform()->SetLocalPosition(float4{ 50.f,-75.f,static_cast<int>(ZOrder::Z00Fx00) });
		}
		Dir_ = AnimationDirection::Right;
	}

}

const bool Player::GroundCollisonUpdate()
{
	ColState_Pixel_ = Map::PixelCollisionTransform(PlayerMovingCollision, 10);
	ColState_Ground = ColState_Pixel_.b_Down;

	return ColState_Ground;
}

const bool Player::ParryCollisonUpdate()
{
	ColState_Parry_ = PlayerParryCollision->Collision(static_cast<int>(CollisionGruop::Parry));

	return ColState_Parry_;
}

const bool Player::HitCollisonUpdate()
{
	ColState_Hit_ = PlayerHitBox->Collision(static_cast<int>(CollisionGruop::Monster));

	if (true == ColState_Hit_)
	{
		float4 MonsterPos = PlayerHitBox->CollisionPtr(static_cast<int>(CollisionGruop::Monster))->GetTransform()->GetWorldPosition();

		HitDir_ = MonsterPos - GetTransform()->GetWorldPosition();
		//HitDir_.Normalize2D();
	}

	return ColState_Hit_;
}

void Player::ImageScaleUpdate() //아직 미사용
{
	float4 size = PlayerImageRenderer->GetImageSize();

	if (PrevAniSize_ != size)
	{
		PrevAniSize_ = size;

		PlayerImageRenderer->GetTransform()->SetLocalScaling(size);
		PlayerMovingCollision->GetTransform()->SetLocalScaling(size);
		//PlayerHitBox->GetTransform()->SetLocalScaling(size);
	}

}

