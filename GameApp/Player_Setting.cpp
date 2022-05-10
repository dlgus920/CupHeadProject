#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PositionComponent.h"

#include "Player.h"
#include "Bullet.h"


void Player::DefalutSetting()
{
	PlayerImageRenderer->SetChangeAnimation("Cup-Idle");

	PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetImageSize());

	Dir_ = AnimationDirection::Right;

	BulletInfo_.BulletSpeed_ = 1000.f;
	BulletInfo_.BulletDamage_ = 10;

	ChangeShootFunc(&Player::ShootDefalutBullet);

	GameState_.ChangeState("Intro");

	ShootingPos_[static_cast<int>(ShootingDir::Right)] = float4{ 80.f,-50.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };
	ShootingPos_[static_cast<int>(ShootingDir::Left)] = float4{ -80.f,-50.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };

	ShootingPos_[static_cast<int>(ShootingDir::Right_Down)] = float4{ 70.f,-100.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };
	ShootingPos_[static_cast<int>(ShootingDir::Left_Down)] = float4{ -70.f,-100.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };

	ShootingPos_[static_cast<int>(ShootingDir::Left_Up)] = float4{ -70.f,-10.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };
	ShootingPos_[static_cast<int>(ShootingDir::Right_Up)] = float4{ 70.f,-10.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };

	ShootingPos_[static_cast<int>(ShootingDir::Up_Left)] = float4{ -25.f,35.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };
	ShootingPos_[static_cast<int>(ShootingDir::Up_Right)] = float4{ 25.f,35.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };

	ShootingPos_[static_cast<int>(ShootingDir::Down_Left)] = float4{ -25.f,-130.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };
	ShootingPos_[static_cast<int>(ShootingDir::Down_Right)] = float4{ 25.f,-130.f,static_cast<int>(ZOrder::Z01Actor01Bullet01) };

	{
		Bottom_Card_ = GetLevel()->CreateActor<Bottom_Card>();
		Bottom_Card_->GetTransform()->SetWorldPosition(float4{ 110.f,-700.f,static_cast<float>(ZOrder::Z00UI) });

		Bottom_HP_ = GetLevel()->CreateActor<Bottom_HP>();
		Bottom_HP_->GetTransform()->SetWorldPosition(float4{ 50.f,-700.f,static_cast<float>(ZOrder::Z00UI) });
	}
}

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
	State_.CreateState("Fall", &Player::Fall_Start, &Player::Fall_Update, &Player::Fall_End);
	State_.CreateState("RockOn", &Player::RockOn_Start, &Player::RockOn_Update, &Player::RockOn_End);
	State_.CreateState("Duck", &Player::Duck_Start, &Player::Duck_Update, &Player::Duck_End);

	State_.CreateState("Bomb", &Player::Bomb_Start, &Player::Bomb_Update, &Player::Bomb_End);
	State_.CreateState("Death", &Player::Death_Start, &Player::Death_Update, &Player::Death_End);
	State_.CreateState("Hit", &Player::Hit_Start, &Player::Hit_Update, &Player::Hit_End);
	State_.CreateState("Dash", &Player::Dash_Start, &Player::Dash_Update, &Player::Dash_End);

	GameState_.CreateState("Intro", &Player::Intro_Start, &Player::Intro_Update, &Player::Intro_End);
	GameState_.CreateState("Playing", &Player::Playing_Start, &Player::Playing_Update, &Player::Playing_End);
	GameState_.CreateState("End", &Player::End_Start, &Player::End_Update, &Player::End_End);
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
		//PlayerImageRenderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f)); //색상 오버레이
		//PlayerImageRenderer->SetAlpha(0.5f); //알파
	}

	{

		PlayerMovingCollision_Top = CreateTransformComponent<GameEngineCollision>();
		PlayerMovingCollision_Top->SetCollisionType(CollisionType::Rect);
		PlayerMovingCollision_Top->SetCollisionGroup(static_cast<int>(CollisionGruop::Player));
		PlayerMovingCollision_Top->GetTransform()->SetLocalMove(float4{ 0.f,-74.f,0.f });
		PlayerMovingCollision_Top->GetTransform()->SetLocalScaling(float4{ 125.f,125.f,1.f });

		PlayerMovingCollision_Middle = CreateTransformComponent<GameEngineCollision>();
		PlayerMovingCollision_Middle->SetCollisionType(CollisionType::Rect);
		PlayerMovingCollision_Middle->SetCollisionGroup(static_cast<int>(CollisionGruop::Player));
		PlayerMovingCollision_Middle->GetTransform()->SetLocalMove(float4{ 0.f,-75.f,0.f });
		PlayerMovingCollision_Middle->GetTransform()->SetLocalScaling(float4{ 125.f,125.f,1.f });

		PlayerMovingCollision_Bot = CreateTransformComponent<GameEngineCollision>();
		PlayerMovingCollision_Bot->SetCollisionType(CollisionType::Rect);
		PlayerMovingCollision_Bot->SetCollisionGroup(static_cast<int>(CollisionGruop::Player));
		PlayerMovingCollision_Bot->GetTransform()->SetLocalMove(float4{ 0.f,-76.f,0.f });
		PlayerMovingCollision_Bot->GetTransform()->SetLocalScaling(float4{ 125.f,125.f,1.f });
	}

	{
		PlayerParryCollision = CreateTransformComponent<GameEngineCollision>();
		PlayerParryCollision->SetCollisionType(CollisionType::Rect);
		PlayerParryCollision->SetCollisionGroup(static_cast<int>(CollisionGruop::PlayerParry));
		PlayerParryCollision->GetTransform()->SetLocalMove(float4{0.f,-75.f,0.f});
		PlayerParryCollision->GetTransform()->SetLocalScaling(float4{ 125.f,125.f,1.f });
	}

	{
		PlayerHitBox = CreateTransformComponent<GameEngineCollision>();
		PlayerHitBox->SetCollisionType(CollisionType::Rect);
		PlayerHitBox->SetCollisionGroup(static_cast<int>(CollisionGruop::PlayerHitBox));
		PlayerHitBox->GetTransform()->SetLocalMove(float4{0.f,-75.f,0.f});
		PlayerHitBox->GetTransform()->SetLocalScaling(float4{50.f,75.f,1.f });

		//PlayerHitBox->Off();
	}
}

void Player::AnimationSetting()
{
	// INTRO
	{
		PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Intro", 220, 247, C_AnimationInterTime_);
		PlayerImageRenderer->SetEndCallBack("Cup-Intro", std::bind(&Player::IntroAniamtionEnd, this));
	}
	// IDLE
	{		
		PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Idle", 0, 7, C_AnimationInterTime_);
	}
	// JUMP
	{
		PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Jump", 20, 27, 0.166f);

		PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Jump-Parry", 120, 127, 0.166f);
	}

	{
		// HIT_GROUND
		{
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Hit-Ground", 28, 33, C_AnimationInterTime_);
		}
		// HIT_AIR
		{
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Hit-Air", 34, 39, C_AnimationInterTime_);
		}
	}

	//WALK
	{
		//SHOOT WHILE WALKING
		{
			//UP
			{
				PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Walk-Shoot-Up", 80,95 , C_AnimationInterTime_);
			}
			//STRAIGHT
			{
				PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Walk-Shoot-Str", 60, 75, C_AnimationInterTime_);
			}
		}
		PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Walk", 40, 55, C_AnimationInterTime_);
		PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Walk-Turn", 57, 58, 0.05f);

		PlayerImageRenderer->SetEndCallBack("Cup-Walk-Turn", std::bind(&Player::WalkState_Changed_End,this));
	}

	//IDLE
	{
		//ROCK-ON
		{
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-RockOn-Up", 206, 210, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-RockOn-Up-Str", 186, 190, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-RockOn-Str", 200, 204, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-RockOn-Down", 192, 196, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-RockOn-Down-Str", 180, 184, C_AnimationInterTime_);
		}
		//DUCK
		{
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Duck-Start", 160, 166, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Duck-Idle", 168, 172, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Duck-Shoot", 174, 176, C_AnimationInterTime_);
		}

		//
		//SHOOT
		{
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Shoot-Up", 116, 118, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Shoot-Up-Str", 108, 110, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Shoot-Str", 100, 102, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Shoot-Down", 112, 114, C_AnimationInterTime_);
			PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Shoot-Down-Str", 104, 106, C_AnimationInterTime_);
		}
	}

	//Dash
	{
		PlayerImageRenderer->CreateLevelAnimation("Cup_Dash.png", "Cup-Dash", 0, 7, C_AnimationInterTime_);
		PlayerImageRenderer->SetEndCallBack("Cup-Dash", std::bind(&Player::DashAniamtionEnd, this));
	}
	PlayerImageRenderer->CreateLevelAnimation("Cup.png", "Cup-Death", 140, 154, C_AnimationInterTime_);
}

