#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineComponent.h"
#include <GameEngineBase/GameEngineTime.h>

class TransformData 
{
public:
	float4 vWorldPosition_;
	float4 vWorldRotation_;
	float4 vWorldScaling_;

	float4 vLocalPosition_;
	float4 vLocalRotation_;
	float4 vLocalScaling_;

	float4x4 LocalScaling_;
	float4x4 LocalRotation_;
	float4x4 LocalPosition_;
	float4x4 LocalWorld_;

	float4x4 Parent_;
	float4x4 WorldWorld_;

	float4x4 View_;
	float4x4 Projection_;

	float4x4 WVP;

public:
	TransformData() 
		: vWorldScaling_(float4::ONE)
		, vLocalScaling_(float4::ONE)
	{

	}

	void LocalCalculation()
	{
		LocalScaling_.Scaling(vLocalScaling_);
		LocalRotation_.RotationDeg(vLocalRotation_);
		LocalPosition_.Translation(vLocalPosition_);

		LocalWorld_ = LocalScaling_ * LocalRotation_ * LocalPosition_;
	}

	void ParentSetting(const float4x4& _Parent) 
	{
		Parent_ = _Parent;
		WorldWorld_ = LocalWorld_;
		WorldWorld_ *= Parent_;
	}

	void CalWVP()
	{
		WVP = WorldWorld_ * View_ * Projection_;
	}

	void RootCalculation() 
	{
		WorldWorld_ = LocalWorld_;
	}
};

// ����̶� 
// ��ġ�� �����ؾ� �Ѵ�. => ���

// ��� ��ġ�� �׷����� �Ѵ�. => ���
// ��� ��ġ���� �ٸ� �ֵ�� �浹�ؾ� �Ѵ� => ���

// ��ġ�� ��Ÿ���� ����̶� ������ ������Ʈ��� �θ��� ���������� �߿��ϴ�.

// �浹�� �̳༮�� ����Ұ��̱� ������ ���ϰ� �߿��ϰ� �߸����� �Ѵ�.
// ���� :
class GameEngineTransform 
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

	void TransformUpdate();

	float4 GetLocalScaling() { return TransformData_.vLocalScaling_; }
	float4 GetWorldScaling() { return TransformData_.vWorldScaling_; }
	float4 GetLocalRotation() { return TransformData_.vLocalRotation_; }
	float4 GetWorldRotation() { return TransformData_.vWorldRotation_; }
	float4 GetLocalPosition() { return TransformData_.vLocalPosition_; }
	float4 GetWorldPosition() { return TransformData_.vWorldPosition_; }

	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0]
	// [0][0][0][1]

	float4 GetWorldForwardVector() { return TransformData_.WorldWorld_.vz.NormalizeReturn3D(); }
	float4 GetLocalForwardVector() { return TransformData_.LocalWorld_.vz.NormalizeReturn3D(); }
	float4 GetWorldRightVector() { return TransformData_.WorldWorld_.vx.NormalizeReturn3D(); }
	float4 GetLocalRightVector() { return TransformData_.LocalWorld_.vx.NormalizeReturn3D(); }
	float4 GetWorldUpVector() { return TransformData_.WorldWorld_.vy.NormalizeReturn3D(); }
	float4 GetLocalUpVector() { return TransformData_.LocalWorld_.vy.NormalizeReturn3D(); }



	void SetLocalScaling(const float4& _Value);
	void SetWorldScaling(const float4& _Value);

	// ����� ��׸�
	void SetLocalRotation(const float4& _Value);
	void SetWorldRotation(const float4& _Value);

	void SetLocalDeltaTimeRotation(const float4& _Value)
	{
		SetLocalRotation(TransformData_.vLocalRotation_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
	}

	void SetWorldDeltaTimeRotation(const float4& _Value)
	{
		SetWorldRotation(TransformData_.vWorldRotation_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
	}

	void SetLocalPosition(const float4& _Value);
	void SetWorldPosition(const float4& _Value);

	void SetLocalMove(const float4& _Value)
	{
		SetLocalPosition(TransformData_.vLocalPosition_ + _Value);
	}

	void SetWorldMove(const float4& _Value)
	{
		SetWorldPosition(TransformData_.vWorldPosition_ + _Value);
	}

	void SetLocalDeltaTimeMove(const float4& _Value)
	{
		SetLocalPosition(TransformData_.vLocalPosition_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
	}

	void SetWorldDeltaTimeMove(const float4& _Value)
	{
		SetWorldPosition(TransformData_.vWorldPosition_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
	}
	
	//
	//void SetLocalDeltaTimeMove(const float4& _Value, float DeltaTime_)
	//{
	//	SetLocalPosition(TransformData_.vLocalPosition_ + _Value * DeltaTime_);
	//}

	//void SetWorldDeltaTimeMove(const float4& _Value, float DeltaTime_)
	//{
	//	SetWorldPosition(TransformData_.vWorldPosition_ + _Value * DeltaTime_);
	//}
	//

	void DetachChildTransform(GameEngineTransform* _Child);
	void AttachTransform(GameEngineTransform* _Transform);

	TransformData& GetTransformData()
	{
		return TransformData_;
	}

	void SetLocalScaling( const float _ValueX, const float _ValueY, const float _ValueZ =0);
	void SetWorldScaling(const float _ValueX, const float _ValueY, const float _ValueZ =0);
	void SetLocalRotation(const float _ValueX, const float _ValueY, const float _ValueZ =0);
	void SetWorldRotation(const float _ValueX, const float _ValueY, const float _ValueZ =0);
	void SetLocalPosition(const float _ValueX, const float _ValueY, const float _ValueZ =0);
	void SetWorldPosition(const float _ValueX, const float _ValueY, const float _ValueZ =0);

protected:
	TransformData TransformData_;

	GameEngineTransform* Parent_;
	std::list<GameEngineTransform*> Childs_;

private:
	void AllChildCalculationScaling();
	void AllChildCalculationRotation();
	void AllChildCalculationPosition();

	void CalculationLocalScaling();
	void CalculationWorldScaling();

	void CalculationWorldRotation();
	void CalculationLocalRotation();

	void CalculationLocalPosition();
	void CalculationWorldPosition();



};

