#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() 
	: Parent_(nullptr)
{
}

GameEngineTransform::~GameEngineTransform() 
{
}

void GameEngineTransform::TransformUpdate() 
{
	TransformData_.LocalCalculation();

	// TransData_.LocalWorld_;
	// [][][][]
	// [][][][]
	// [][][][]
	// [][][][]

	// TransData_.WorldWorld_;
	// [][][][]
	// [][][][]
	// [][][][]
	// [][][][]

	if (nullptr != Parent_)
	{
		TransformData_.ParentSetting(Parent_->TransformData_.WorldWorld_);
	}
	else {
		TransformData_.RootCalculation();
	}

	for (GameEngineTransform* ChildTransform_ : Childs_)
	{
		ChildTransform_->TransformUpdate();
	}
}

void GameEngineTransform::AllChildCalculationScaling()
{
	for (auto& Child : Childs_)
	{
		// �θ��� ũ�Ⱑ �ٲ���̰� �θ��� ũ�Ⱑ �ٲ���ٴ°���
		// �ڽ��� ���� �������� �ٲ���ٴ°��� �ǹ��Ѵ�.
		Child->CalculationWorldScaling();
		Child->CalculationWorldPosition();
		Child->AllChildCalculationScaling();
	}
}

void GameEngineTransform::AllChildCalculationRotation() 
{
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldRotation();
		Child->CalculationWorldPosition();
		Child->AllChildCalculationRotation();
	}
}

void GameEngineTransform::AllChildCalculationPosition()
{
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldPosition();
		Child->AllChildCalculationPosition();
	}
}

void GameEngineTransform::CalculationWorldScaling() 
{
	TransformData_.vWorldScaling_ = Parent_->TransformData_.vWorldScaling_ * TransformData_.vLocalScaling_;
}

void GameEngineTransform::CalculationLocalScaling()
{
	TransformData_.vLocalScaling_ = TransformData_.vWorldScaling_ / Parent_->TransformData_.vWorldScaling_;
}

void GameEngineTransform::CalculationWorldRotation() 
{
	TransformData_.vWorldRotation_ = Parent_->TransformData_.vWorldRotation_ + TransformData_.vLocalRotation_;
}

void GameEngineTransform::CalculationLocalRotation() 
{
	TransformData_.vLocalRotation_ = TransformData_.vWorldRotation_ - Parent_->TransformData_.vWorldRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	float4 WorldPostion = TransformData_.vWorldPosition_ - Parent_->TransformData_.vWorldPosition_;

	WorldPostion.Rotate3DDegree(-Parent_->TransformData_.vWorldRotation_);

	WorldPostion /= Parent_->TransformData_.vWorldScaling_;

	TransformData_.vLocalPosition_ = WorldPostion;
}


void GameEngineTransform::CalculationWorldPosition()
{
	float4 CalLocalPos = TransformData_.vLocalPosition_;
	// ũ�⸦ Ű���
	CalLocalPos *= Parent_->TransformData_.vWorldScaling_;
	// ȸ����Ű��
	CalLocalPos.Rotate3DDegree(Parent_->TransformData_.vWorldRotation_);
	// �θ��� ��ġ�� �̵��Ѱ�
	CalLocalPos += Parent_->TransformData_.vWorldPosition_;

	TransformData_.vWorldPosition_ = CalLocalPos;
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalScaling_ = _Value;
		TransformData_.vWorldScaling_ = _Value;
		AllChildCalculationScaling();
		return;
	}

	TransformData_.vLocalScaling_ = _Value;
	CalculationWorldScaling();
	AllChildCalculationScaling();
}



void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalScaling_ = _Value;
		TransformData_.vWorldScaling_ = _Value;
		AllChildCalculationScaling();
		return;
	}

	TransformData_.vWorldScaling_ = _Value;
	CalculationLocalScaling();
	AllChildCalculationScaling();
}

// ����� ��׸�
void GameEngineTransform::SetLocalRotation(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalRotation_ = _Value;
		TransformData_.vWorldRotation_ = _Value;
		AllChildCalculationRotation();
		return;
	}

	TransformData_.vLocalRotation_ = _Value;
	CalculationWorldRotation();
	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldRotation(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalRotation_ = _Value;
		TransformData_.vWorldRotation_ = _Value;
		AllChildCalculationRotation();
		return;
	}

	TransformData_.vWorldRotation_ = _Value;
	CalculationLocalRotation();
	AllChildCalculationRotation();
}


void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalPosition_ = _Value;
		TransformData_.vWorldPosition_ = _Value;
		AllChildCalculationPosition();
		return;
	}

	TransformData_.vLocalPosition_ = _Value;
	CalculationWorldPosition();
	AllChildCalculationPosition();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value) 
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalPosition_ = _Value;
		TransformData_.vWorldPosition_ = _Value;
		AllChildCalculationPosition();
		return;
	}

	TransformData_.vWorldPosition_ = _Value;
	CalculationLocalPosition();
	AllChildCalculationRotation();
}

void GameEngineTransform::DetachChildTransform(GameEngineTransform* _Transform)
{
	Childs_.remove(_Transform);
}

void GameEngineTransform::AttachTransform(GameEngineTransform* _Transform)
{
	// ���� �������� _Parent�� ����ٳ�� �մϴ�.

	if (nullptr != Parent_)
	{
		Parent_->DetachChildTransform(this);
	}

	Parent_ = _Transform;
	Parent_->Childs_.push_back(this);
}

