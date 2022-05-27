#include "PreCompile.h"
#include "Player.h"
#include "Map.h"
#include "Image.h"
#include "UserGame.h"
#include "GameEngine/GameEngineCollision.h"

#ifdef _DEBUG
void Player::Update_DEBUG()
{
	//GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect);

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

	//KeyUpdate();
		//GroundCollisonUpdate();
		//ParryCollisonUpdate();
		//HitCollisonUpdate();
		//StateUpdate(_DeltaTime);

		//ImageScaleUpdate();

		//GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect);

		//State_Update_는 State_.Update중에 설정함

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
	//ColState_Ground_Top_ = Map::PixelGroundCollisionTransform(PlayerMovingCollision_Top, 5);
	ColState_Ground_Middle_ = Map::PixelGroundCollisionTransform(PlayerMovingCollision_Middle, 5);
	ColState_Ground_Bot_ = Map::PixelGroundCollisionTransform(PlayerMovingCollision_Bot, 5);

	ColState_Ground_Floar_ = PlayerMovingCollision_Bot->Collision(static_cast<int>(CollisionGruop::FloarCard));

	if (ColState_Ground_Bot_ && ColState_Ground_Middle_)
	{
		PlayerGround_Stuck_ = true;
	}

	if (ColState_Ground_Bot_ && !ColState_Ground_Middle_)
	{
		PlayerGround_Stuck_ = false;
	}

	return PlayerGround_Stuck_;
}

const bool4 Player::SideCollisonUpdate()
{
	return ColState_Pixel_ = Map::PixelSideCollisionTransform(PlayerMovingCollision_Middle, 10);
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

