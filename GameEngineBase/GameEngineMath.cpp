#include "PreCompile.h"
#include "GameEngineMath.h"


const float GameEngineMath::PI = 3.14159265359f;
const float GameEngineMath::PI2 = 3.14159265359f * 2;
const float GameEngineMath::DegreeToRadian = GameEngineMath::PI / 180.0f;
const float GameEngineMath::RadianToDegree = 180.0f / GameEngineMath::PI;

// Static Var
// Static Func

const float4 float4::ZERO = { 0.0f, 0.0f };
const float4 float4::ONE = { 1.0f, 1.0f, 1.0f, 1.0f };

const float4 float4::LEFT = { -1.0f, 0.0f };
const float4 float4::RIGHT = { 1.0f, 0.0f };
const float4 float4::UP = { 0.0f, 1.0f };
const float4 float4::DOWN = { 0.0f, -1.0f };
const float4 float4::UPLEFT = { -0.70710f, 0.70710f };
const float4 float4::UPRIGHT = { 0.70710f, 0.70710f };
const float4 float4::DOWNLEFT = { -0.70710f, -0.70710f };
const float4 float4::DOWNRIGHT = { 0.70710f, -0.70710f };



const float4 float4::RED = { 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
const float4 float4::WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
const float4 float4::BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::NONE = { 0.0f, 0.0f, 0.0f, 0.0f };

float4 float4::RotateYRadian(const float4& _OriginVector, float _Radian)
{
	float4x4 Rot;
	Rot.RotationYRad(_Radian);
	return _OriginVector * Rot;
}

float4 float4::RotateXRadian(const float4& _OriginVector, float _Radian)
{
	float4x4 Rot;
	Rot.RotationXRad(_Radian);
	return _OriginVector * Rot;
}

float4 float4::RotateZRadian(const float4& _OriginVector, float _Radian)
{
	float4x4 Rot;
	Rot.RotationZRad(_Radian);
	return _OriginVector * Rot;
}

float4 float4::DirZRadian(float _Radian)
{
	float4x4 Rot;
	Rot.RotationZRad(_Radian);
	return float4::RIGHT * Rot;
}



float4 float4::operator*(const float4x4& _Value) const
{
	return DirectX::XMVector4Transform(DirectVector, _Value.DirectMatrix);
}

float4& float4::operator*=(const float4x4& _Value)
{
	DirectVector = DirectX::XMVector4Transform(DirectVector, _Value.DirectMatrix);
	return *this;
}

