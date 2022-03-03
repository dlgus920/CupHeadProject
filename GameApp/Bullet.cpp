#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Bullet.h"

Bullet::Bullet() :
	MoveDir_()
{

}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	// 정말 세팅해줘야할게 많은 녀석입니다.
	// 랜더러로서 뭐든지 다 그릴수있는 가능성을 가지고 있는 녀석.
	{
		ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		//Renderer->SetRenderingPipeLine("Color");
		//Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
		//Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 1.0f, 1.0f));

		ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

		ImageRenderer_->SetImage("Char.png");
		ImageRenderer_->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f }); 
		
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("Color");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 20.0f, 1.0f });
		Renderer->GetTransform()->SetLocalPosition({ 0.0f, 80.0f, 0.0f });
		Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
	}
}

void Bullet::TransformUpdate()
{
}

void Bullet::Update(float _DeltaTime)
{
	//GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 200.0f);
}

void Bullet::ReleaseEvent()
{
}
