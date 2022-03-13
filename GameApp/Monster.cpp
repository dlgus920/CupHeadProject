#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include "Monster.h"
#include "Bullet.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}



void Monster::Start()
{
	// 정말 세팅해줘야할게 많은 녀석입니다.
	// 랜더러로서 뭐든지 다 그릴수있는 가능성을 가지고 있는 녀석.
	//{
	//	GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	//	Renderer->SetRenderingPipeLine("Color");
	//	Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
	//	Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(0.0f, 0.0f, 0.0f));
	//}

	{
		ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		ImageRenderer->SetImage("Animation.png");
		ImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
		ImageRenderer->CreateAnimation("Test", 5, 20, 0.5f);
		ImageRenderer->SetChangeAnimation("Test"); 
	}

}

void Monster::TransformUpdate()
{
}

void Monster::Update(float _DeltaTime)
{

}

void Monster::ReleaseEvent()
{
}
