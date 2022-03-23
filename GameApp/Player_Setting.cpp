#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Bullet.h"

void Player::KeySetting()
{
	GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
	GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
	GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
	GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
	GameEngineInput::GetInst().CreateKey("Jump", 'Z');
	GameEngineInput::GetInst().CreateKey("Fire", 'X');
	GameEngineInput::GetInst().CreateKey("Dash", 'C');
	GameEngineInput::GetInst().CreateKey("Bomb", 'V');
	//GameEngineInput::GetInst().CreateKey("Fire", VK_SPACE);
}

void Player::StateSetting()
{
	State_.CreateState("Idle", &Player::Idle_Start, &Player::Idle_Update);
	State_.CreateState("Walk", &Player::Walk_Start, &Player::Walk_Update);
	State_.CreateState("Jump", &Player::Jump_Start, &Player::Jump_Update);
	State_.CreateState("RockOn", &Player::RockOn_Start, &Player::RockOn_Update);
	State_.CreateState("Duck", &Player::Duck_Start, &Player::Duck_Update);

	State_.CreateState("Bomb", &Player::Bomb_Start, &Player::Bomb_Update);
	State_.CreateState("Death", &Player::Death_Start, &Player::Death_Update);
	State_.CreateState("Hit", &Player::Hit_Start, &Player::Hit_Update);
	State_.CreateState("Dash", &Player::Dash_Start, &Player::Dash_Update);

}

void Player::ComponentSetting()
{
	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
	}

	{
		//BulletPoint_ = CreateTransformComponent<GameEngineTransform>();
		//BulletPoint_->SetLocalPosition(float4{ 50.f,0.f,1.f });
	}

	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>();
		PlayerCollision->CreateCollision<CollisionGruop>
			(CollisionType::Rect,CollisionGruop::Player, float4{ 100.0f, 100.0f, 1.0f });

		//PlayerCollision->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
		//PlayerCollision->SetCollisionGroup<CollisionGruop>(CollisionGruop::Player);
	}

	{
		PlayerHitBox = CreateTransformComponent<GameEngineCollision>();
		PlayerHitBox->CreateCollision<CollisionGruop>
			(CollisionType::Rect, CollisionGruop::PlayerHitBox, float4{ 100.0f, 100.0f, 1.0f });
	}
}

void Player::AnimationSetting()
{
	// IDLE
	{		
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Idle", 0, 7, 0.1f);
	}
	// JUMP
	{
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Jump", 20, 27, 0.1f);
	}

	{
		// HIT_GROUND
		{
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Hit-Ground", 28, 33, 0.1f);
		}
		// HIT_AIR
		{
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Hit-Air", 34, 39, 0.1f);
		}
	}

	//WALK
	{
		//SHOOT WHILE WALKING
		{
			//UP
			{
				PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Walk-Shoot-Up", 80,95 , 0.1f);
			}
			//STRAIGHT
			{
				PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Walk-Shoot-Straight", 60, 75, 0.1f);
			}
		}
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Walk", 40, 55, 0.1f);
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Walk-Turn", 57, 58, 0.1f);
	}

	//IDLE
	{
		//ROCK-ON
		{
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-RockOn-Up", 206, 210, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-RockOn-Up-Str", 186, 190, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-RockOn-Str", 200, 204, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-RockOn-Down", 192, 196, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-RockOn-Down-Str", 180, 184, 0.1f);
		}
		//DUCK
		{
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Duck-Start", 160, 166, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Duck-Idle", 168, 172, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Duck-Shoot", 174, 179, 0.1f);

		}

		//
		//SHOOT
		{
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Shoot-Up", 116, 118, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Shoot-Up-Str", 108, 110, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Shoot-Str", 100, 102, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Shoot-Down", 112, 114, 0.1f);
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Shoot-Down-Str", 104, 106, 0.1f);
		}
	}

	PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Dash", 20, 27, 0.1f);
	PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Death", 140, 154, 0.1f);
}