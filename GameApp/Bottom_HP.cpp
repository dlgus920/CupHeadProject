#include "PreCompile.h"
#include "Bottom_HP.h"

Bottom_HP::Bottom_HP()
	: HPBarRenderer_(nullptr)
	, CurHP_(8)
{

}

Bottom_HP::~Bottom_HP() // default destructer 디폴트 소멸자
{

}

void Bottom_HP::Start()
{
	HPBarRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	HPBarRenderer_->CreateAnimation("Bottom_HP.png","Idle", 0, 10, 999999.f, false);
	HPBarRenderer_->CreateAnimation("Bottom_HP.png","HP1", 1, 3, 0.05f, true);

	HPBarRenderer_->SetChangeAnimation("Idle");

	GetTransform()->SetLocalScaling(float4{81.f,35.f,1.f});
}

void Bottom_HP::Update(float _DeltaTime)
{

		HPBarRenderer_->GetCurrentAnimation()->GetCurrentIndex();
}

void Bottom_HP::HPIncrease()
{
	if (CurHP_ != 8)
	{
		++CurHP_;
		HPBarRenderer_->SetChangeAnimation("Idle");
		HPBarRenderer_->GetCurrentAnimation()->SetCurrentIndex(CurHP_ + 2);
	}
}

void Bottom_HP::HPDecrease()
{
	if (CurHP_ != 0)
	{
		--CurHP_;
	}

	if (CurHP_ == 0)
	{
		HPBarRenderer_->SetChangeAnimation("Idle");
		HPBarRenderer_->GetCurrentAnimation()->SetCurrentIndex(CurHP_);
	}
	else if (CurHP_ == 1)
	{
		HPBarRenderer_->SetChangeAnimation("HP1");
	}
	else
	{
		HPBarRenderer_->SetChangeAnimation("Idle");
		HPBarRenderer_->GetCurrentAnimation()->SetCurrentIndex(CurHP_+2);
	}
}