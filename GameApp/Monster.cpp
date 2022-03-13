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
	// ���� ����������Ұ� ���� �༮�Դϴ�.
	// �������μ� ������ �� �׸����ִ� ���ɼ��� ������ �ִ� �༮.
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
