#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"

#include "TopUI.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/MouseActor.h>

#include "Map.h"
#include "Image.h"
#include "Bullet.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::LevelStart() 
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Camera00)));

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition(float4(900.f, -400.0f, static_cast<int>(ZOrder::Z01Actor01)));
	}

	GameEngineInput::GetInst().CreateKey("TEST", VK_LSHIFT);
	//SetDebug(false);
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{
	if (GameEngineInput::GetInst().Press("TEST"))
	{
		Bullet_Defalut* Bullet = CreateActor<Bullet_Defalut>();
		float4 pos = Player_->GetTransform()->GetWorldPosition();
		Bullet->GetTransform()->SetWorldPosition(float4{ pos.x, pos.y, 0.3f });
		Bullet->SetMoveDir(float4::RIGHT);
	}
}
void PlayLevel::LevelChangeEndEvent()
{

}
void PlayLevel::LevelChangeStartEvent()
{

}
