#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"

#include "ParryObject.h"

#include <GameEngine/GameEngineCore.h>

//#include <GameEngine/GameEngineImageRenderer.h>


void Player::Idle_Start()
{
	ChangeAnimation("Cup-Idle");

	while (ColUpdate_Ground())
	{
		Move(float4(0.f, 1.f, 0.f), 1.f);
	}

	if (true == ColState_Ground_Floar_)
	{
		float a = -320.f;

		while (GetTransform()->GetWorldPosition().y < a)
		{
			Move(float4(0.f, 1.f, 0.f), 1.f);
		}
	}
}
void Player::Idle_Update(float _DeltaTime)
{
	if (CheckState() != "Idle")
	{
		State_.ChangeState(CheckState());
		return;
	}

	if (false == ColState_Ground_Bot_)
	{
		if (false == ColState_Ground_Floar_)
		{
			State_.ChangeState("Fall");
			return;
		}
	}

	if (KeyState_Shoot_)
	{
		IsShooting_ = true;

		ShootingInterTime_ += _DeltaTime;
		
		if (true == KeyState_Up_)
		{
			if (Dir_ == AnimationDirection::Left)
			{
				ChangeAnimation("Cup-Shoot-Up");
				BulletInfo_.MoveDir_ = float4::UP;
				ShootingDir_ = ShootingDir::Up_Left;
			}
			else
			{
				ChangeAnimation("Cup-Shoot-Up");
				BulletInfo_.MoveDir_ = float4::UP;
				ShootingDir_ = ShootingDir::Up_Right;
			}
		}

		else if (Dir_ == AnimationDirection::Left)
		{
			ChangeAnimation("Cup-Shoot-Str");
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left;
		}

		else if(Dir_ == AnimationDirection::Right)
		{
			ChangeAnimation("Cup-Shoot-Str");
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right;
		}

		if (ShootingInterTime_ >= ShootingTime_)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}
	else
	{
		IsShooting_ = false;
		ShootingInterTime_ = 0.f;

		ChangeAnimation("Cup-Idle");
	}
}
void Player::Idle_End()
{
	ShootingInterTime_ = 0.f;
	TimeCheck_ = 0.f;
}

void Player::Walk_Start()
{
	TimeCheck_ = 0.f;
	// 각기 다른 에니메이션 재생
}
void Player::Walk_Update(float _DeltaTime)
{
	TimeCheck_ -= _DeltaTime;

	if (true == ColState_Ground_Floar_)
	{
		if (true == KeyState_Down_ && KeyState_Jump_)
		{
			State_.ChangeState("Fall");
			return;
		}
	}

	if (false == ColState_Ground_Bot_)
	{
		if (false == ColState_Ground_Floar_)
		{
			State_.ChangeState("Fall");
			return;
		}
	}

	if (TimeCheck_ <= 0.f)
	{
		EffectDust();
		TimeCheck_ = 0.3f;
	}

	if (true == WalkState_Changed_)
	{
		ChangeAnimation("Cup-Walk-Turn");
	}

	if (CheckState() != "Walk")
	{
		State_.ChangeState(CheckState());
		return;
	}

	if (false == WalkState_Changed_)
	{
		if (KeyState_Shoot_)
		{
			IsShooting_ = true;

			ShootingInterTime_ += _DeltaTime;

			ChangeAnimation("Cup-Walk-Shoot-Str");

			if (Dir_ == AnimationDirection::Left)
			{
				BulletInfo_.MoveDir_ = float4::LEFT;
				ShootingDir_ = ShootingDir::Left;
			}
			else
			{
				BulletInfo_.MoveDir_ = float4::RIGHT;
				ShootingDir_ = ShootingDir::Right;
			}

			if (ShootingInterTime_ >= ShootingTime_)
			{
				BulletShootFunc_();
				ShootingInterTime_ = 0.f;
			}
		}
		else
		{
			IsShooting_ = false;

			ShootingInterTime_ = 0.f;

			ChangeAnimation("Cup-Walk");
		}

		if (KeyState_Right_)
		{
			if (ColState_Right_ == false)
			{
				Move(400.f, 0.f, _DeltaTime);
			}
		}
		else
		{
			if (ColState_Left_ == false)
			{
				Move(-400.f, 0.f, _DeltaTime);
			}
		}
	}
}
void Player::Walk_End()
{
	ShootingInterTime_ = 0.f;
	TimeCheck_ = 0.f;
}

void Player::Jump_Start()
{
	ChangeAnimation("Cup-Jump");

	Move(0.f, 10.f, 0.f);

	Jumpend_ = false;
	LongJump_ = false;
	Parry_ = false;
	JumpSpeed_ = 0.f;
	TimeCheck_ = 0.f;
	ShootingInterTime_ = 0.f;

	JumpAcc_ = C_JumpSpeed0_ / 0.35f;

	Player_FX_Channel_->PlayLevelOverLap("sfx_player_jump_01.wav");

	EffectDust();
}
void Player::Jump_Update(float _DeltaTime)
{
	//TODO :: 언젠가 점프 더 부드럽게 다듬을것

	if (true == ColState_Hit_)
	{
		TimeCheck_ = 0.f;
		State_.ChangeState("Hit");
		return;
	}

	if (true == KeyState_Dash_) 
	{
		TimeCheck_ = 0.f;
		State_.ChangeState("Dash");
		return;
	}

	if (true == KeyState_Bomb)
	{
		TimeCheck_ = 0.f; 
		State_.ChangeState("Bomb");
		return;
	}

	TimeCheck_ += _DeltaTime;

	if (true == ColState_Parry_)
	{
		if (false == Parry_)
		{
			if (GameEngineInput::GetInst().Down("Jump"))
			{
				Parry_ = true; // 페리중이다.

				GameEngineCollision* parrycol = PlayerParryCollision->CollisionPtr(static_cast<int>(CollisionGruop::Parry));
				dynamic_cast<ParryObject*>(parrycol->GetActor())->Parry(parrycol);

				Player_FX_Channel_->PlayLevelOverLap("sfx_player_parry_slap_01.wav");

				ChangeAnimation("Cup-Jump-Parry");

				ParryEffect = GetLevel()->CreateActor<GameEngineActor>();

				ParryEffect->DeathTime_ = 1.f;

				GameEngineImageRenderer* ParryRenderer;

				float4 pos = PlayerParryCollision->GetTransform()->GetWorldPosition();
				pos.z += 1.f;

				ParryRenderer = ParryEffect->CreateTransformComponent<GameEngineImageRenderer>();
				ParryRenderer->GetTransform()->SetLocalScaling(float4{712.f,712.f} );
				ParryRenderer->GetTransform()->SetWorldPosition(pos);
				ParryRenderer->SetLevelImage("ParryEffect_A.png");

				ParryRenderer = ParryEffect->CreateTransformComponent<GameEngineImageRenderer>();
				ParryRenderer->GetTransform()->SetLocalScaling(float4{ 712.f,712.f });
				ParryRenderer->GetTransform()->SetWorldPosition(pos);
				ParryRenderer->SetLevelImage("ParryEffect_B.png");

				EffectParry();

				UIBase::UIBase_->GetBottom_Card()->Increase();
				
				Jumpend_ = false;
				LongJump_ = false;
				JumpSpeed_ = 0.f;
				TimeCheck_ = 0.f;
			}
		}
	}

	if (true == Parry_)
	{
		Parrytimecheck_ += GameEngineTime::GetInst().GetDeltaTime();

		if (Parrytimecheck_ < 0.2f)
		{
			GameEngineCore::SetTimeRate(0.0f);
		}
		else
		{
			if (nullptr != ParryEffect)
			{
				ParryEffect->Death();
				ParryEffect = nullptr;
			}

			GameEngineCore::SetTimeRate(1.f);
			Parrytimecheck_ = 0.f;
			Parry_ = false;
		}

		if (TimeCheck_ < 0.35f)
		{
			JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
			Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
		}

		else if (TimeCheck_ >= 0.35f)
		{
			if (false == Jumpend_)
			{
				Jumpend_ = true;
				JumpSpeed_ = 0.f;
			}

			Parry_ = false;
		}
	}

	if (false == Parry_)
	{
		if (TimeCheck_ < 0.2f)
		{
			if (true == KeyState_Jump_Press)
			{
				LongJump_ = true;
			}
			else
			{
				LongJump_ = false;
			}

			JumpSpeed_ -= (JumpAcc_ * _DeltaTime);

			Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
		}

		else if(TimeCheck_ >= 0.2f)
		{
			if (true == LongJump_)
			{
				if (TimeCheck_ < 0.30f)
				{
					Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
				}

				else if (TimeCheck_ < 0.45f)
				{
					JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
					Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
				}

				if (TimeCheck_ >= 0.55f)
				{
					if (false == Jumpend_)
					{
						Jumpend_ = true;
						JumpSpeed_ = 0.f;
					}

					JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
					Move(float4(0.f, JumpSpeed_, 0.f), _DeltaTime);


					if (PlayerMovingCollision_Bot->GetTransform()->GetWorldPosition().y < 150.f)
					{
						if (true == ColState_Ground_Floar_)
						{
							State_.ChangeState("Idle");
							return;
						}

						if (true == ColState_Ground_Bot_)
						{
							State_.ChangeState("Idle");
							return;
						}
					}
				}
			}

			else if (false == LongJump_)
			{
				if (TimeCheck_ < 0.35f)
				{	
					JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
					Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
				}

				if (TimeCheck_ >= 0.35f)
				{
					if (false == Jumpend_)
					{
						Jumpend_ = true;
						JumpSpeed_ = 0.f;
					}

					JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
					Move(float4(0.f, JumpSpeed_, 0.f), _DeltaTime);

					if (PlayerMovingCollision_Bot->GetTransform()->GetWorldPosition().y < 150.f)
					{
						if (true == ColState_Ground_Floar_)
						{
							State_.ChangeState("Idle");
							return;
						}

						if (true == ColState_Ground_Bot_)
						{
							State_.ChangeState("Idle");
							return;
						}
					}
				}
			}
		}
	}

	if (KeyState_Right_)
	{
		if (ColState_Right_ == false)
		{
			Move(C_MoveSpeed_, 0.f, _DeltaTime); 
			
			if (Map::PixelCollisionTransform(PlayerMovingCollision_Middle, 10).b_Right)
			{
				Move(-C_MoveSpeed_, 0.f, _DeltaTime *-1.f);
			}
		}
	}
	else if (KeyState_Left_)
	{
		if (ColState_Left_ == 0.f)
		{
			Move(-C_MoveSpeed_, 0.f, _DeltaTime);

			if (Map::PixelCollisionTransform(PlayerMovingCollision_Middle, 10).b_Left)
			{
				Move(C_MoveSpeed_, 0.f, _DeltaTime * -1.f);
			}
		}
	}

	if (KeyState_Shoot_)
	{
		IsShooting_ = true;

		ShootingInterTime_ += _DeltaTime;

		if (Dir_ == AnimationDirection::Left)
		{
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left;
		}
		else
		{
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right;
		}

		if (ShootingInterTime_ >= ShootingTime_)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}
	else
	{
		IsShooting_ = false;
		ShootingInterTime_ = 0.f;
	}
}
void Player::Jump_End()
{
	GameEngineCore::SetTimeRate(1.f);
	EffectJumpLanding();

	Jumpend_ = false;
	LongJump_ = false;
	Parry_ = false;
	JumpSpeed_ = 0.f;
	TimeCheck_ = 0.f;
	ShootingInterTime_ = 0.f;
}

void Player::Fall_Start()
{
	ChangeAnimation("Cup-Jump");

	TimeCheck_ = 0.f;

	JumpAcc_ = C_JumpSpeed0_ / 0.35f;
}
void Player::Fall_Update(float _DeltaTime)
{
	if (true == ColState_Hit_)
	{
		TimeCheck_ = 0.f;
		State_.ChangeState("Hit");
		return;
	}

	if (true == KeyState_Dash_)
	{
		TimeCheck_ = 0.f;
		State_.ChangeState("Dash");
		return;
	}

	if (true == KeyState_Bomb)
	{
		TimeCheck_ = 0.f;
		State_.ChangeState("Bomb");
		return;
	}

	if (true == ColState_Parry_)
	{
		if (false == Parry_)
		{
			if (GameEngineInput::GetInst().Down("Jump"))
			{
				Parry_ = true; // 페리중이다.

				GameEngineCollision* parrycol = PlayerParryCollision->CollisionPtr(static_cast<int>(CollisionGruop::Parry));
				dynamic_cast<ParryObject*>(parrycol->GetActor())->Parry(parrycol);

				ChangeAnimation("Cup-Jump-Parry");

				EffectParry();

				UIBase::UIBase_->GetBottom_Card()->Increase();

				Jumpend_ = false;
				LongJump_ = false;
				JumpSpeed_ = 0.f;
				TimeCheck_ = 0.f;
			}
		}
	}

	if (true == Parry_)
	{
		if (TimeCheck_ < 0.35f)
		{
			GameEngineCore::SetTimeRate(0.3f);

			JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
			Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
		}

		else if (TimeCheck_ >= 0.35f)
		{
			GameEngineCore::SetTimeRate(1.f);
			if (false == Jumpend_)
			{
				Jumpend_ = true;
				JumpSpeed_ = 0.f;
			}

			Parry_ = false;
		}
	}

	JumpSpeed_ -= (JumpAcc_ * _DeltaTime);
	Move(float4(0.f, JumpSpeed_, 0.f), _DeltaTime);

	if (true == ColState_Ground_Bot_)
	{
			State_.ChangeState("Idle");
			return;
	}

	if (KeyState_Right_)
	{
		if (ColState_Right_ == false)
		{
			Move(C_MoveSpeed_, 0.f, _DeltaTime);
		}
	}
	else if (KeyState_Left_)
	{
		if (ColState_Left_ == false)
		{
			Move(-C_MoveSpeed_, 0.f, _DeltaTime);
		}
	}

	if (KeyState_Shoot_)
	{
		IsShooting_ = true;

		ShootingInterTime_ += _DeltaTime;

		if (Dir_ == AnimationDirection::Left)
		{
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left;
		}
		else
		{
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right;
		}

		if (ShootingInterTime_ >= ShootingTime_)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}
	else
	{
		IsShooting_ = false;

		ShootingInterTime_ = 0.f;
	}
}
void Player::Fall_End()
{
	GameEngineCore::SetTimeRate(1.f);
	EffectJumpLanding();

	Jumpend_ = false;
	LongJump_ = false;
	Parry_ = false;
	JumpSpeed_ = 0.f;
	TimeCheck_ = 0.f;
	ShootingInterTime_ = 0.f;
}

void Player::Duck_Start()
{
	ChangeAnimation("Cup-Duck-Idle");
}
void Player::Duck_Update(float _DeltaTime)
{
	if (true == ColState_Ground_Floar_)
	{
		if (true == KeyState_Down_)
		{
			if (true == KeyState_Jump_)
			{
				State_.ChangeState("Fall");
				return;
			}
		}
	}

	if (CheckState() != "Duck")
	{
		State_.ChangeState(CheckState());
		return;
	}

	if (KeyState_Shoot_)
	{
		IsShooting_ = true;

		ShootingInterTime_ += _DeltaTime;

		ChangeAnimation("Cup-Duck-Shoot");
		if (Dir_ == AnimationDirection::Right)
		{
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right_Down;
		}
		else
		{
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left_Down;
		}

		if (ShootingInterTime_ >= ShootingTime_)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}
	else
	{
		IsShooting_ = false;

		ChangeAnimation("Cup-Duck-Idle");
		ShootingInterTime_ = 0.f;
	}
}
void Player::Duck_End()
{
	ShootingInterTime_ = 0.f;
}

void Player::RockOn_Start()
{
}
void Player::RockOn_Update(float _DeltaTime)
{
	if (CheckState() != "RockOn")
	{
		State_.ChangeState(CheckState());
		return;
	}

	if (true == KeyState_Shoot_)
	{
		IsShooting_ = true;

		ShootingInterTime_ += _DeltaTime;

		if (KeyState_Down_ && !KeyState_Up_)
		{
			if (Dir_ == AnimationDirection::Left)
			{
				if (true == KeyState_Left_)
				{
					ChangeAnimation("Cup-Shoot-Down-Str");
					BulletInfo_.MoveDir_ = float4::LEFTDOWN;
					ShootingDir_ = ShootingDir::Left_Down;
				}
				else
				{
					ChangeAnimation("Cup-Shoot-Down");
					BulletInfo_.MoveDir_ = float4::DOWN;
					ShootingDir_ = ShootingDir::Down_Left;
				}
			}

			else if (Dir_ == AnimationDirection::Right)
			{
				if (true == KeyState_Right_)
				{
					ChangeAnimation("Cup-Shoot-Down-Str");
					BulletInfo_.MoveDir_ = float4::RIGHTDOWN;
					ShootingDir_ = ShootingDir::Right_Down;
				}
				else
				{
					ChangeAnimation("Cup-Shoot-Down");
					BulletInfo_.MoveDir_ = float4::DOWN;
					ShootingDir_ = ShootingDir::Down_Right;
				}
			}
		}

		else if (KeyState_Up_ && !KeyState_Down_)
		{
			if (Dir_ == AnimationDirection::Left)
			{
				if (true == KeyState_Left_)
				{
					ChangeAnimation("Cup-Shoot-Up-Str");
					BulletInfo_.MoveDir_ = float4::LEFTUP;
					ShootingDir_ = ShootingDir::Left_Up;
				}
				else
				{
					ChangeAnimation("Cup-Shoot-Up");
					BulletInfo_.MoveDir_ = float4::UP;
					ShootingDir_ = ShootingDir::Up_Left;
				}
			}

			else if (Dir_ == AnimationDirection::Right)
			{
				if (true == KeyState_Right_)
				{
					ChangeAnimation("Cup-Shoot-Up-Str");
					BulletInfo_.MoveDir_ = float4::RIGHTUP;
					ShootingDir_ = ShootingDir::Right_Up;
				}
				else
				{
					ChangeAnimation("Cup-Shoot-Up");
					BulletInfo_.MoveDir_ = float4::UP;
					ShootingDir_ = ShootingDir::Up_Right;
				}
			}
		}

		else if (Dir_ == AnimationDirection::Left)
		{
			ChangeAnimation("Cup-Shoot-Str");
			BulletInfo_.MoveDir_ = float4::LEFT;
			ShootingDir_ = ShootingDir::Left;
		}

		else if (Dir_ == AnimationDirection::Right)
		{
			ChangeAnimation("Cup-Shoot-Str");
			BulletInfo_.MoveDir_ = float4::RIGHT;
			ShootingDir_ = ShootingDir::Right;
		}

		if (ShootingInterTime_ >= ShootingTime_)
		{
			BulletShootFunc_();
			ShootingInterTime_ = 0.f;
		}
	}

	else if(false == KeyState_Shoot_)
	{
		IsShooting_ = false;
		
		ShootingInterTime_ = 0.f;

		if (true == KeyState_Up_)
		{
			if (KeyState_Left_ ||
				KeyState_Right_)
			{
				ChangeAnimation("Cup-RockOn-Up-Str");			
			}

			else
			{
				ChangeAnimation("Cup-RockOn-Up");				
			}
		}

		else if (true == KeyState_Down_)
		{
			if (KeyState_Left_||
				KeyState_Right_)
			{
				ChangeAnimation("Cup-RockOn-Down-Str");
			}

			else
			{
				ChangeAnimation("Cup-RockOn-Down");
			}
		}

		else
		{
			ChangeAnimation("Cup-RockOn-Str");
		}
	}
}
void Player::RockOn_End()
{
	IsShooting_ = false;

	ShootingInterTime_ = 0.f;
}

void Player::Bomb_Start()
{
	ChangeAnimation("Cup-Bomb");

}
void Player::Bomb_Update(float _DeltaTime)
{
	//if(ani end)
	{
		State_.ChangeState(CheckState());
		return;
	}
}
void Player::Bomb_End()
{
	TimeCheck_ = 0.f;
}

void Player::Death_Start()
{
}
void Player::Death_Update(float _DeltaTime)
{
	if (true) // 조건 충족시
	{
		//return "Idle";
	}
	else
	{
		return void();

	}
}
void Player::Death_End()
{
}

void Player::Hit_Start()
{
	IsShooting_ = false;

	//GameEngineCore::SetTimeRate(0.5f);
	Player_FX_Channel_->PlayLevelOverLap("sfx_player_hit_01.wav");
	Player_FX_Channel_->PlayLevelOverLap("sfx_player_damage_crack_level4.wav");

	EffectHit();

	if (true == ColState_Ground_Bot_)
	{
		ChangeAnimation("Cup-Hit-Ground");
	}
	else
	{
		ChangeAnimation("Cup-Hit-Air");
	}

	HitInvince_ = true;

	UIBase::UIBase_->GetBottom_HP()->HPDecrease();
	TimeCheck_ = 0.f;

	JumpAcc_ = C_JumpSpeed0_ / 0.35f;
}
void Player::Hit_Update(float _DeltaTime)
{
	//if (Bottom_HP_->GetCurHP() == 0)
	//{
	//	return "Death";
	//}

	TimeCheck_ += _DeltaTime;

	if (TimeCheck_ < 0.35f)
	{
		JumpSpeed_ -= (JumpAcc_ * _DeltaTime);

		if (GetTransform()->GetWorldPosition().y < 80.f)
		{
			Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);
		}	
	}

	else if (TimeCheck_ >= 0.35f)
	{
		JumpSpeed_ -= (JumpAcc_ * _DeltaTime);

		Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), _DeltaTime);

		if (PlayerMovingCollision_Bot->GetTransform()->GetWorldPosition().y < 150.f)
		{
			if (Map::PixelGroundCollisionTransform(PlayerMovingCollision_Bot, 5))
			{
				Move(float4(0.f, C_JumpSpeed0_ + JumpSpeed_, 0.f), -_DeltaTime);
				State_.ChangeState("Idle");
				return;
			}
		}
	}

	if (HitDir_.x > 0.f)
	{
		if (ColState_Left_ == 0.f)
		{
			Move(-400.f, 0.f, _DeltaTime);

			if (Map::PixelCollisionTransform(PlayerMovingCollision_Middle, 5).b_Left)
			{
				Move(400.f, 0.f, _DeltaTime);
			}
		}
	}
	else if (HitDir_.x < 0.f)
	{
		if (ColState_Right_ == false)
		{
			Move(400.f, 0.f, _DeltaTime);

			if (Map::PixelCollisionTransform(PlayerMovingCollision_Middle, 5).b_Right)
			{
				Move(-400.f, 0.f, _DeltaTime);
			}
		}
	}
}
void Player::Hit_End()
{
	JumpSpeed_ = 0.f;
	TimeCheck_ = 0.f;
	//GameEngineCore::SetTimeRate(1.f);
}

void Player::Dash_Start()
{
	PlayerHitBox->Off();

	Player_FX_Channel_->PlayLevelOverLap("sfx_player_dash_01.wav");
	EffectDashDust();
	ChangeAnimation("Cup-Dash");
	AniState_DashEnd_ = false;
}
void Player::Dash_Update(float _DeltaTime)
{
	if ((Dir_ == AnimationDirection::Right))
	{
		Move(C_DashSpeed_, 0.f, _DeltaTime);
	}
	else
	{
		Move(-C_DashSpeed_, 0.f, _DeltaTime);
	}

	if(true == AniState_DashEnd_)
	{
		State_.ChangeState(CheckState());
		return;
	}
}
void Player::Dash_End()
{
	PlayerHitBox->On();
	AniState_DashEnd_ = false;
}





void Player::Intro_Start()
{
	Player_FX_Channel_->PlayLevelOverLap("sfx_player_intro_cuphead.wav");

	PlayerImageRenderer->SetChangeAnimation("Cup-Intro");
}
void Player::Intro_Update(float _DeltaTime)
{
	if (true == AniState_IntroEnd_)
	{
		GameState_.ChangeState("Playing");
		return;
	}
}
void Player::Intro_End()
{
	AniState_IntroEnd_ = false;
}

void Player::Playing_Start()
{
	State_.ChangeState("Idle");
}
void Player::Playing_Update(float _DeltaTime)
{
	if (true == Update_State_)
	{
		KeyUpdate();
	}
	CollisionUpdate();
	ParryCollisonUpdate();
	HitCollisonUpdate();
	StateUpdate(_DeltaTime);
	SoundUpdate(_DeltaTime);

	if (true == HitInvince_)
	{
		//반짝임 효과zz

		HitInvinceTimeCheck_ += _DeltaTime;

		PlayerHitBox->Off();
		//컬리젼 해제

		if (blit_)
		{
			PlayerImageRenderer->SetResultColor(float4{ 1.f,1.f,1.f,0.6f });
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
}
void Player::Playing_End()
{

}

void Player::End_Start()
{
	//이게 호출될때 바닥에 착지한 상태일것, (필히 자연스러운 흐름으로 Idle State에서 넘어오게 만들것,)

	ChangeAnimation("Cup-Idle");
}
void Player::End_Update(float _DeltaTime) 
{
}
void Player::End_End() 
{

}