#include "PreCompile.h"
#include "Player.h"
#include "Map.h"
#include "GameEngine/GameEngineCollision.h"

void Player::Update(float _DeltaTime)
{
	//GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);  //����� ������ ����

	//GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	if (true == KeyState_Update_)
	{
		KeyUpdate();
	}

	if (true == ColState_Update_)
	{
		CollisonUpdate(); // �ø��� ������Ʈ���� ����� �浹 ���θ� �˻��ϰ�, stateupdate������ �����ϵ��� �Ѵ�.
	}

	if (true == State_Update_)
	{
		StateUpdate(_DeltaTime);
	}

	ImageScaleUpdate();

	//GetLevel()->PushDebugRender(PlayerHitBox->GetTransform(), CollisionType::Rect);

	//State_Update_�� State_.Update�߿� ������
}

void Player::StateUpdate(float _DeltaTime)
{
	State_.Update(_DeltaTime);
}

void Player::KeyUpdate()
{
	KeyState_Left_ = GameEngineInput::GetInst().Press("MoveLeft");
	KeyState_Right_ = GameEngineInput::GetInst().Press("MoveRight");

	if (KeyState_Left_ && !KeyState_Right_)
	{
		if (Dir_ == AnimationDirection::Right)
			GetTransform()->SetHorizenInvertTransform();
		Dir_ = AnimationDirection::Left;
	}

	else if (KeyState_Right_ && !KeyState_Left_)
	{
		if (Dir_ == AnimationDirection::Left)
			GetTransform()->SetHorizenInvertTransform();
		Dir_ = AnimationDirection::Right;
	}

	KeyState_Up_ = GameEngineInput::GetInst().Press("MoveUp");
	KeyState_Down_ = GameEngineInput::GetInst().Press("MoveDown");

	KeyState_Shoot_ = GameEngineInput::GetInst().Press("Fire");

	KeyState_RockOn_ = GameEngineInput::GetInst().Press("RockOn");
	//KeyState_Bomb = GameEngineInput::GetInst().Press("Bomb");
	//KeyState_Jump_ = GameEngineInput::GetInst().Press("Jump");
	//KeyState_Dash_ = GameEngineInput::GetInst().Press("Dash");
}

void Player::CollisonUpdate()
{
	ColState_Hit_ = PlayerHitBox->Collision(static_cast<int>(CollisionGruop::Bullet));

	ColState_Ground = Map::PixelCollision(PlayerCollision, 10);
}

void Player::ImageScaleUpdate() //���� �̻��
{
	if (CurAnimation_ != PlayerImageRenderer->GetCurrentAnimationName())
	{
		CurAnimation_ = PlayerImageRenderer->GetCurrentAnimationName();
		PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetImageSize());
		PlayerCollision->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetImageSize());
		PlayerHitBox->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetImageSize());
	}

}

