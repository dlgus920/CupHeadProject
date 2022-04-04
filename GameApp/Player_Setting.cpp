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
	GameEngineInput::GetInst().CreateKey("Fire2", 'Z');
	GameEngineInput::GetInst().CreateKey("Fire", 'X');
}

void Player::StateSetting()
{
	State_.CreateState("Idle", &Player::Idle_Start, &Player::Idle_Update, &Player::Idle_End);
	State_.CreateState("Walk", &Player::Walk_Start, &Player::Walk_Update, &Player::Walk_End);

}

void Player::ComponentSetting()
{
	PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
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
				PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Walk-Shoot-Str", 60, 75, 0.1f);
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
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Duck-Shoot", 174, 176, 0.1f);

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