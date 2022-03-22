#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Bullet.h"


void Player::ComponentSetting()
{
	//BulletPoint_ = CreateComponent<GameEngineTransformComponent>();
	//BulletPoint_->AttachTransform(GetTransform());
}

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

	State_.CreateState("Bomb", &Player::Bomb_Start, &Player::Bomb_Update);
	State_.CreateState("Death", &Player::Death_Start, &Player::Death_Update);
	State_.CreateState("Hit", &Player::Hit_Start, &Player::Hit_Update);
	State_.CreateState("Dash", &Player::Dash_Start, &Player::Dash_Update);

}

void Player::RendererSetting()
{
	PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(static_cast<int>(RenderOrder::Player));

	PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
}

void Player::TransformSetting()
{
	// 이거 ㅣㄹ요해?
	//GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>();
	//Renderer->SetRenderingPipeLine("Color");
	//Renderer->GetTransform()->SetLocalScaling({ 100.0f, 20.0f, 1.0f });
	//Renderer->GetTransform()->SetLocalPosition({ 0.0f, 80.0f, 0.0f });
	//Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
}

void Player::CollisionSetting()
{
	//{
	//	PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>();
	//	//PlayerImageRenderer->SetImage("Char.png");
	//	PlayerImageRenderer->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
	//}
	
	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>();
		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
		PlayerCollision->SetCollisionGroup<CollisionGruop>(CollisionGruop::Player);
	}

	{
		PlayerHitBox = CreateTransformComponent<GameEngineCollision>();
		PlayerHitBox->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
		PlayerHitBox->SetCollisionGroup<CollisionGruop>(CollisionGruop::PlayerHitBox);
	}
}

void Player::AnimationSetting()
{
	// IDLE
	{		
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Idle", 0, 4, 0.1f);
	}
	// HIT-GROUND
	{
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Hit-Ground", 5, 10, 0.1f);
	}
	// HIT-AIR
	{
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Hit-Air", 29, 34, 0.1f);
		
	}
	// RUN
	{
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Run", 5, 20, 0.5f);
	}
	// SHOOT
	{
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Shoot", 5, 20, 0.5f);
	}
	// JUMP
	{
		PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Jump", 20, 27, 0.5f);
	}

	{
		// HIT_GROUND
		{
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-HitGround", 20, 27, 0.5f);
		}
		// HIT_AIR
		{
			PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-HitAir", 20, 27, 0.5f);
		}
	}

	//WALK
	{
		//SHOOT WHILE WALKING
		{
			//UP
			{
				PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Walk-Shoot-Up", 20, 27, 0.5f);
			}
			//STRAIGHT
			{
				PlayerImageRenderer->CreateAnimation("Cup.png", "Cup-Walk-Shoot-Straight", 20, 27, 0.5f);
			}

		}
	}

	//IDLE
	{
		//ROCK-ON

		//DUCK

		//



	}

	//JUMP
	{

	}
}