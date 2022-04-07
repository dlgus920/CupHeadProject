#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PositionComponent.h"

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
	GameEngineInput::GetInst().CreateKey("RockOn", 'C');
	GameEngineInput::GetInst().CreateKey("Dash", VK_LSHIFT);
	//GameEngineInput::GetInst().CreateKey("Bomb", 'V');
	//GameEngineInput::GetInst().CreateKey("Fire", VK_SPACE);
}

void Player::StateSetting()
{
	State_.CreateState("Idle", &Player::Idle_Start, &Player::Idle_Update, &Player::Idle_End);
	State_.CreateState("Walk", &Player::Walk_Start, &Player::Walk_Update, &Player::Walk_End);
	State_.CreateState("Jump", &Player::Jump_Start, &Player::Jump_Update, &Player::Jump_End);
	State_.CreateState("RockOn", &Player::RockOn_Start, &Player::RockOn_Update, &Player::RockOn_End);
	State_.CreateState("Duck", &Player::Duck_Start, &Player::Duck_Update, &Player::Duck_End);

	State_.CreateState("Bomb", &Player::Bomb_Start, &Player::Bomb_Update, &Player::Bomb_End);
	State_.CreateState("Death", &Player::Death_Start, &Player::Death_Update, &Player::Death_End);
	State_.CreateState("Hit", &Player::Hit_Start, &Player::Hit_Update, &Player::Hit_End);
	State_.CreateState("Dash", &Player::Dash_Start, &Player::Dash_Update, &Player::Dash_End);
	State_.CreateState("Parry", &Player::Parry_Start, &Player::Parry_Update, &Player::Parry_End);

}

void Player::ComponentSetting()
{
	{
		//GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		//Renderer->SetRenderingPipeLine("Color");
		//Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
	}

	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
		
		//PlayerImageRenderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f)); //���� ��������
		//PlayerImageRenderer->SetAlpha(0.5f); //����
	}

	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>();
		PlayerCollision->SetCollisionType(CollisionType::Rect);
		PlayerCollision->SetCollisionGroup(static_cast<int>(CollisionGruop::Player));

		//PlayerCollision->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
	}

	{
		PlayerHitBox = CreateTransformComponent<GameEngineCollision>();
		PlayerHitBox->SetCollisionType(CollisionType::Rect);
		PlayerHitBox->SetCollisionGroup(static_cast<int>(CollisionGruop::PlayerHitBox));
	}

	{
		BulletPointOrigin_ = CreateTransformComponent<PositionComponent>();
		BulletPointOrigin_->GetTransform()->SetLocalPosition(float4{ 0.f,-50.f,static_cast<int>(ZOrder::Z00Bullet01) });

		BulletPoint_ = CreateTransformComponent<PositionComponent>(BulletPointOrigin_->GetTransform());
		BulletPoint_->GetTransform()->SetLocalPosition(float4{ 0.f,0.f,static_cast<int>(ZOrder::Z00Bullet01) });
		//BulletPoint_->GetTransform()->SetWorldPosition(float4{ 0.f,0.f,static_cast<int>(ZOrder::Z00Bullet01) });
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

	//Dash
	{
		PlayerImageRenderer->CreateAnimation("Cup_Dash.png", "Cup-Dash", 0, 7, 0.1f);
	}
	PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Death", 140, 154, 0.1f);
}