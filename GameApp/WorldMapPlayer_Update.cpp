#include "PreCompile.h"
#include "WorldMapPlayer.h"

void WorldMapPlayer::Update(float _DeltaTime)
{
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	if (true == KeyState_Update_)
	{
		KeyUpdate();
	}

	if (true == ColState_Update_)
	{
		CollisonUpdate(); // 컬리젼 업데이트에서 상대방과 충돌 여부를 검사하고, stateupdate에서ㅏ 참고하도록 한다.
	}

	if (true == State_Update_)
	{
		StateUpdate(_DeltaTime);
	}
}

void WorldMapPlayer::StateUpdate(float _DeltaTime)
{
	State_.Update(_DeltaTime);
}

void WorldMapPlayer::KeyUpdate()
{
	KeyState_Left_ = GameEngineInput::GetInst().Press("MoveLeft");
	KeyState_Right_ = GameEngineInput::GetInst().Press("MoveRight");
	KeyState_Up_ = GameEngineInput::GetInst().Press("MoveUp");
	KeyState_Down_ = GameEngineInput::GetInst().Press("MoveDown");
	KeyState_Chose_ = GameEngineInput::GetInst().Down("Chose");

	if (KeyState_Down_ && !KeyState_Up_)
	{
		if (KeyState_Left_ && !KeyState_Right_)
		{
			if (Dir_ == AnimationDirection::Right)
				GetTransform()->SetHorizenInvertTransform();
			Dir_ = AnimationDirection::Left;

			MoveDir_ = float4::LEFTDOWN;
		}

		else if (KeyState_Right_ && !KeyState_Left_)
		{
			if (Dir_ == AnimationDirection::Left)
				GetTransform()->SetHorizenInvertTransform();
			Dir_ = AnimationDirection::Right;

			MoveDir_ = float4::RIGHTDOWN;
		}

		else
			MoveDir_ = float4::DOWN;
	}

	else if (KeyState_Up_ && !KeyState_Down_)
	{
		if (KeyState_Left_ && !KeyState_Right_)
		{
			if (Dir_ == AnimationDirection::Right)
				GetTransform()->SetHorizenInvertTransform();
			Dir_ = AnimationDirection::Left;

			MoveDir_ = float4::LEFTUP;
		}

		else if (KeyState_Right_ && !KeyState_Left_)
		{
			if (Dir_ == AnimationDirection::Left)
				GetTransform()->SetHorizenInvertTransform();
			Dir_ = AnimationDirection::Right;

			MoveDir_ = float4::RIGHTUP;
		}

		else
			MoveDir_ = float4::UP;
	}

	else if (KeyState_Left_ && !KeyState_Right_)
	{
		if (Dir_ == AnimationDirection::Right)
			GetTransform()->SetHorizenInvertTransform();
		Dir_ = AnimationDirection::Left;

		MoveDir_ = float4::LEFT;
	}

	else if (KeyState_Right_ && !KeyState_Left_)
	{
		if (Dir_ == AnimationDirection::Left)
			GetTransform()->SetHorizenInvertTransform();
		Dir_ = AnimationDirection::Right;

		MoveDir_ = float4::RIGHT;
	}
}

void WorldMapPlayer::CollisonUpdate()
{
	ColState_ = Map::PixelCollisionTransform(PlayerCollision->GetTransform(), 10);

	GameEngineCollision* Collision = PlayerCollision->CollisionPtr
	(static_cast<int>(CollisionGruop::StagePoint));

	if (nullptr != Collision)
	{
		ColState_Chose_ = dynamic_cast<StagePoint*>(Collision->GetActor());
	}

	//float4 Color = Map::GetColor(GetTransform());

	//if (Color == float4::BLACK)
	//{
	//	ColState_ = true;
	//}
}
