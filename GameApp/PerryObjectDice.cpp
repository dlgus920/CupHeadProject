#include "PreCompile.h"
#include "PerryObjectDice.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>

PerryObjectDice::PerryObjectDice()
	: DiceNumber_(DiceNumber::None)
	, ObjectRenderer_(nullptr)
	, King_Dice_(nullptr)
	, Rolled_(false)
{

}

PerryObjectDice::~PerryObjectDice() // default destructer 디폴트 소멸자
{

}

void PerryObjectDice::Start()
{
	ParryCollision = CreateTransformComponent<GameEngineCollision>();
	ParryCollision->GetTransform()->SetLocalScaling(float4{100.f,100.f,1.f });
	ParryObjectSetColOption(CollisionType::Rect, CollisionGruop::Parry);

	ObjectRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();

	ObjectRenderer_->CreateLevelAnimation("ParryObjectDice.png","Idle",50,73,0.05,true);

	ObjectRenderer_->CreateLevelAnimation("ParryObjectDice.png","Rolling1-1",0,4, 0.05, false);
	ObjectRenderer_->CreateLevelAnimation("ParryObjectDice.png","Rolling1-2",20,22, 0.05, false);

	ObjectRenderer_->CreateLevelAnimation("ParryObjectDice.png", "Rolling2-1", 5, 9, 0.05, false);
	ObjectRenderer_->CreateLevelAnimation("ParryObjectDice.png", "Rolling2-2", 23, 25, 0.05, false);

	ObjectRenderer_->CreateLevelAnimation("ParryObjectDice.png", "Rolling3-1", 10, 14, 0.05, false);
	ObjectRenderer_->CreateLevelAnimation("ParryObjectDice.png", "Rolling3-2", 26, 28, 0.05, false);

	ObjectRenderer_->CreateLevelAnimation("ParryObjectDice.png","Death",30,47, 0.05,false);// 57프레임 도달시 업데이트 멈춤

	//ObjectRenderer_->CreateAnimation("ParryObjectDice.png","Num1",50,73, 0.05,true);
	//ObjectRenderer_->CreateAnimation("ParryObjectDice.png","Num2",50,73, 0.05,true);
	//ObjectRenderer_->CreateAnimation("ParryObjectDice.png","Num3",50,73, 0.05,true);

	ObjectRenderer_->SetFrameCallBack("Idle",50,std::bind(&PerryObjectDice::Num1, this));
	ObjectRenderer_->SetFrameCallBack("Idle",57, std::bind(&PerryObjectDice::Num2, this));
	ObjectRenderer_->SetFrameCallBack("Idle",65, std::bind(&PerryObjectDice::Num3, this));

	ObjectRenderer_->SetEndCallBack("Rolling1-1", std::bind(&PerryObjectDice::Rolling1_2, this));
	ObjectRenderer_->SetEndCallBack("Rolling2-1", std::bind(&PerryObjectDice::Rolling2_2, this));
	ObjectRenderer_->SetEndCallBack("Rolling3-1", std::bind(&PerryObjectDice::Rolling3_2, this));

	ObjectRenderer_->SetEndCallBack("Rolling1-2", std::bind(&PerryObjectDice::RollingEnd, this));
	ObjectRenderer_->SetEndCallBack("Rolling2-2", std::bind(&PerryObjectDice::RollingEnd, this));
	ObjectRenderer_->SetEndCallBack("Rolling3-2", std::bind(&PerryObjectDice::RollingEnd, this));

	ObjectRenderer_->SetChangeAnimation("Idle");
	ObjectRenderer_->SetAdjustImzgeSize();
}

void PerryObjectDice::Update(float _DeltaTime)
{
	if (true == UserGame::StageInfo_.Debug_)
	{
		GetLevel()->PushDebugRender(ParryCollision->GetTransform(), CollisionType::Rect);
	}

	if (true == Parry_)
	{
		switch (DiceNumber_)
		{
		case DiceNumber::Num1:
			ObjectRenderer_->SetChangeAnimation("Rolling1-1");
			break;
		case DiceNumber::Num2:
			ObjectRenderer_->SetChangeAnimation("Rolling2-1");
			break;
		case DiceNumber::Num3:
			ObjectRenderer_->SetChangeAnimation("Rolling3-1");
			break;
		}

		Parry_ = false;
	}
}

void PerryObjectDice::Resset() //Spawn과 동시에 Resset 해야함
{
	ObjectRenderer_->SetChangeAnimation("Idle");
	On();
}

void PerryObjectDice::Num1()
{
	DiceNumber_ = DiceNumber::Num1;
}
void PerryObjectDice::Num2()
{
	DiceNumber_ = DiceNumber::Num2;
}
void PerryObjectDice::Num3()
{
	DiceNumber_ = DiceNumber::Num3;
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
	Rolled_ = true;
	ObjectRenderer_->SetChangeAnimation("Death");

	GameEngineRandom rand;

	int randint = rand.RandomInt(1, 4);

	std::string str = "kingdice_laugh_00";

	std::string numstr = std::to_string(randint);

	str = str + numstr + ".wav";
	
	GameEngineSoundManager::GetInst().PlaySoundChannel("Effect", str);
}



