#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player.h"
#include "Bullet.h"


void Player::ComponentSetting()
{
	BulletPoint_ = CreateComponent<GameEngineTransformComponent>();
	BulletPoint_->AttachTransform(GetTransform());
}

void Player::KeySetting()
{
	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
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
	PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	PlayerImageRenderer->SetImage("Char.png");
	PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
}

void Player::TransformSetting()
{
	GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	Renderer->SetRenderingPipeLine("Color");
	Renderer->GetTransform()->SetLocalScaling({ 100.0f, 20.0f, 1.0f });
	Renderer->GetTransform()->SetLocalPosition({ 0.0f, 80.0f, 0.0f });
	Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
}

void Player::CollisionSetting()
{
}
