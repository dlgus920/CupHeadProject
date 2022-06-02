#include "PreCompile.h"
#include "Player.h"
#include "Map.h"
#include "Image.h"
#include "GameEngine/GameEngineCollision.h"

#ifdef _DEBUG
void Player::Update_DEBUG()
{
	//GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect);

	if (PlayerMovingCollision_Middle->Collision(static_cast<int>(CollisionGruop::MonsterAttack)))
	{
		GetLevel()->PushDebugRender(PlayerMovingCollision_Middle->GetTransform(), CollisionType::Rect, float4::PINK);
	}
	else
	{
		GetLevel()->PushDebugRender(PlayerMovingCollision_Middle->GetTransform(), CollisionType::Rect, float4::BLUE);
	}

	if (PlayerParryCollision->Collision(static_cast<int>(CollisionGruop::MonsterAttack)))
	{
		GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect, float4::PINK);
	}
	else
	{
		GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect, float4::BLUE);
	}

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
	GameState_.Update(_DeltaTime);

	if (true == GameEngineInput::GetInst().Down("Debug"))
	{
		if (true == UserGame::StageInfo_.Debug_)
		{
			UserGame::StageInfo_.Debug_ = false;
		}
		else
		{
			UserGame::StageInfo_.Debug_ = true;
		}
	}

	if (true == UserGame::StageInfo_.Debug_)
	{
		Update_DEBUG();
	}



	if (GetTransform()->GetWorldPosition().y < -560.f)
	{
		int a = 0;
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

void Player::SoundUpdate(float _DeltaTime)
{
	if (true == IsShooting_)
	{
		if (false == Shoot_Channel_->IsPlay())
		{
			Shoot_Channel_->PlayLevelOverLap("sfx_player_default_fire_loop_01.wav");
		}
	}
	else
	{
		Shoot_Channel_->Stop();
	}
}

void Player::CollisionUpdate()
{
	ColUpdate_Left();
	ColUpdate_Right();
	ColUpdate_Up();
	ColUpdate_Ground();
}

const bool Player::ColUpdate_Ground()
{
	ColState_Ground_Middle_ = Map::PixelGroundCollisionTransform(PlayerMovingCollision_Middle, 5);
	ColState_Ground_Bot_ = Map::PixelGroundCollisionTransform(PlayerMovingCollision_Bot, 5);

	PlayerGround_Stuck_ = false;

	if (ColState_Ground_Bot_ && ColState_Ground_Middle_)
	{
		PlayerGround_Stuck_ = true;
	}

	if (ColState_Ground_Bot_ && !ColState_Ground_Middle_)
	{
		PlayerGround_Stuck_ = false;
	}

	ColState_Ground_Floar_ = PlayerMovingCollision_Bot->Collision(static_cast<int>(CollisionGruop::FloarCard));

	return PlayerGround_Stuck_;
}

const bool Player::ColUpdate_Left()
{
	ColState_Left_ = Map::PixelLeftCollisionTransform(PlayerMovingCollision_Middle, 5);
	return ColState_Left_;
}

const bool Player::ColUpdate_Right()
{
	ColState_Right_ = Map::PixelRightCollisionTransform(PlayerMovingCollision_Middle, 5);
	return ColState_Right_;
}

const bool Player::ColUpdate_Up()
{
	ColState_Up_ = Map::PixelUpCollisionTransform(PlayerMovingCollision_Middle, 5);
	return ColState_Up_;
}

const bool Player::ParryCollisonUpdate()
{
	ColState_Parry_ = PlayerParryCollision->Collision(static_cast<int>(CollisionGruop::Parry));

	return ColState_Parry_;
}

const bool Player::HitCollisonUpdate()
{
	ColState_Hit_ = PlayerHitBox->Collision(static_cast<int>(CollisionGruop::MonsterAttack));

	if (true == ColState_Hit_)
	{
		float4 MonsterPos = PlayerHitBox->CollisionPtr(static_cast<int>(CollisionGruop::MonsterAttack))->GetTransform()->GetWorldPosition();

		MonsterPos -= GetTransform()->GetWorldPosition();

		if (MonsterPos.x > 0)
		{
			HitDir_ = float4::RIGHT;
		}
		else
		{
			HitDir_ = float4::LEFT;
		}
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
	}

}

