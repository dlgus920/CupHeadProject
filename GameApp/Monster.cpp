#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include "Monster.h"

Monster::Monster() :
	State_(this),
	MonsterHitBox(nullptr),
	MonsterGroundCollision(nullptr),
	MonsterImageRenderer(nullptr),
	CurState_()

{
}

Monster::~Monster()
{
}

void Monster::ChangeAnimation(std::string _animation)
{
	MonsterImageRenderer->SetChangeAnimation(_animation);
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
		ImageRenderer->CreateAnimation("Animation.png","Test", 5, 20, 0.5f);
		ImageRenderer->SetChangeAnimation("Test"); 
		ImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
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
