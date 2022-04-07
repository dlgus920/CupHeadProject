#include "PreCompile.h"
#include "PerryObjectDice.h"

PerryObjectDice::PerryObjectDice()
	: IsCollision_(false)
	, DiceNumber_(DiceNumber::Num1)
{

}

PerryObjectDice::~PerryObjectDice() // default destructer ����Ʈ �Ҹ���
{

}

void PerryObjectDice::Start()
{
	Object::Start();

	ObjectCollision_->GetTransform()->SetLocalScaling(float4{ 50.f,50.f,1.f });
	ObjectCollision_->SetCollisionType(CollisionType::Rect);
	ObjectCollision_->SetCollisionGroup<CollisionGruop>(CollisionGruop::Parry);

	ObjectRenderer_->GetTransform()->SetLocalScaling(float4{ 50.f,50.f,1.f });
	ObjectRenderer_->CreateAnimation("ParryObjectDice","Idle",50,73,true);

	ObjectRenderer_->CreateAnimation("ParryObjectDice","Rolling1-1",0,4, false);
	ObjectRenderer_->CreateAnimation("ParryObjectDice","Rolling1-2",20,22, false);

	ObjectRenderer_->CreateAnimation("ParryObjectDice", "Rolling2-1", 5, 9, false);
	ObjectRenderer_->CreateAnimation("ParryObjectDice", "Rolling2-2", 23, 25, false);

	ObjectRenderer_->CreateAnimation("ParryObjectDice", "Rolling3-1", 10, 14, false);
	ObjectRenderer_->CreateAnimation("ParryObjectDice", "Rolling3-2", 26, 28, false);

	ObjectRenderer_->CreateAnimation("ParryObjectDice","Death",40,57,false);// 57������ ���޽� ������Ʈ ����
	ObjectRenderer_->SetFrameCallBack("Death",57,std::bind(&PerryObjectDice::Off, this));



	ObjectRenderer_->CreateAnimation("ParryObjectDice","Num1",50,73,true);
	ObjectRenderer_->CreateAnimation("ParryObjectDice","Num2",50,73,true);
	ObjectRenderer_->CreateAnimation("ParryObjectDice","Num3",50,73,true);

	ObjectRenderer_->SetFrameCallBack("Idle",0,std::bind(&PerryObjectDice::Num1, this));
	ObjectRenderer_->SetFrameCallBack("Idle",7, std::bind(&PerryObjectDice::Num2, this));
	ObjectRenderer_->SetFrameCallBack("Idle",15, std::bind(&PerryObjectDice::Num3, this));

	ObjectRenderer_->SetEndCallBack("Rolling1-1", std::bind(&PerryObjectDice::Rolling1_1, this));
	ObjectRenderer_->SetEndCallBack("Rolling2-1", std::bind(&PerryObjectDice::Rolling2_1, this));
	ObjectRenderer_->SetEndCallBack("Rolling3-1", std::bind(&PerryObjectDice::Rolling3_1, this));

	ObjectRenderer_->SetEndCallBack("Rolling1-2", std::bind(&PerryObjectDice::RollingEnd, this));
	ObjectRenderer_->SetEndCallBack("Rolling2-2", std::bind(&PerryObjectDice::RollingEnd, this));
	ObjectRenderer_->SetEndCallBack("Rolling3-2", std::bind(&PerryObjectDice::RollingEnd, this));
}

void PerryObjectDice::Update(float _DeltaTime)
{
	if (false == IsCollision_)
	{
		if (ObjectCollision_->Collision(static_cast<int>(CollisionGruop::PlayerHitBox)))
		{
			switch (DiceNumber_)
			{
			case DiceNumber::Num1:
				ObjectRenderer_->SetChangeAnimation("Rolling1-1");
				break;
			case DiceNumber::Num2:
				ObjectRenderer_->SetChangeAnimation("Rolling1-1");
				break;
			case DiceNumber::Num3:
				ObjectRenderer_->SetChangeAnimation("Rolling1-1");
				break;
			}

			IsCollision_ = true;
		}
	}
}

void PerryObjectDice::Resset() //Spawn�� ���ÿ� Resset �ؾ���
{
	IsCollision_ = false;
	ObjectRenderer_->SetChangeAnimation("Idle");
	On();
}

void PerryObjectDice::Rolling1_1()
{
	ObjectRenderer_->SetChangeAnimation("Rolling1-1");
}

void PerryObjectDice::Rolling2_1()
{
	ObjectRenderer_->SetChangeAnimation("Rolling1-1");
}

void PerryObjectDice::Rolling3_1()
{
	ObjectRenderer_->SetChangeAnimation("Rolling1-1");
}

void PerryObjectDice::Rolling1_2()
{
	ObjectRenderer_->SetChangeAnimation("Rolling1-2");
}

void PerryObjectDice::Rolling2_2()
{
	ObjectRenderer_->SetChangeAnimation("Rolling2-2");
}

void PerryObjectDice::Rolling3_2()
{
	ObjectRenderer_->SetChangeAnimation("Rolling3-2");
}

void PerryObjectDice::RollingEnd()
{
	ObjectRenderer_->SetChangeAnimation("Death");
}



