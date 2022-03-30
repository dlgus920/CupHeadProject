#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Map.h"

Map* Map::CurrentMap = nullptr;

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{

}

void Map::LevelChangeStartEvent()
{
	CurrentMap = this;
}

float4 Map::GetColor(GameEngineTransform* _Ptr, bool YRevers /*= true*/)
{
	float4 Pos = _Ptr->GetWorldPosition();

	if (true == YRevers)
	{
		Pos.y *= -1.0f;
	}

	return GetColor(Pos);
}

float4 Map::GetColor(float4 _Postion)
{
	//TODO : 이새끼가 얻어올 픽셀의 좌표를 어쩌구 저쩌구
	return CurrentMap->CollisionMap_->GetCurrentTexture()->GetPixel(_Postion.ix(), _Postion.iy());
}

float4 Map::GetColor(int _Postion_x, int _Postion_y)
{
	return CurrentMap->CollisionMap_->GetCurrentTexture()->GetPixel(_Postion_x, _Postion_y);
}

bool Map::PixelCollision(GameEngineTransform* _Transform, int Precission_coefficient/*10*/)
{
	//회전은 고려하지 않음
	//일일이 검사하면 느리니까 한 면을 Precission_coefficient만큼 등분하여 for문으로 검사, 

	float4 size = _Transform->GetWorldScaling(); // ex) 100.f ,100.f;

	float4 Pos = _Transform->GetWorldPosition();
	Pos.y *= -1.0f;

	// 각각의 4개의 선분의 시작, 종료 지점

	RECT Rect = {static_cast<int>(Pos.x - size.x / 2)  ,static_cast<int>(Pos.y - size.y / 2),
				 static_cast<int>(Pos.x + size.x / 2) ,static_cast<int>(Pos.y + size.y / 2)};
	
	// 각 가로 세로를 10등분 함

	int HorizenConst = static_cast<int>(size.x / Precission_coefficient);
	int VerticalConst = static_cast<int>(size.y / Precission_coefficient);

	for (int i = Rect.left; i < Rect.right; i+= HorizenConst)
	{
		if (GetColor(i, Rect.top) == float4::BLACK ||
			GetColor(i, Rect.bottom) == float4::BLACK)
		{
			return true;
		}
	}

	//정확도를 위한 끝자리 검사
	if (GetColor(Rect.right, Rect.top) == float4::BLACK ||
		GetColor(Rect.right, Rect.bottom) == float4::BLACK)
	{
		return true;
	}

	for (int i = Rect.top; i < Rect.bottom; i += VerticalConst)
	{
		if (GetColor(Rect.left, i) == float4::BLACK ||
			GetColor(Rect.right, i) == float4::BLACK)
		{
			return true;
		}
	}

	//정확도를 위한 끝자리 검사
	if (GetColor(Rect.left, Rect.top) == float4::BLACK ||
		GetColor(Rect.right, Rect.bottom) == float4::BLACK)
	{
		return true;
	}

	return false;
}

bool Map::PixelCollision(GameEngineCollision* _Collision, int Precission_coefficient)
{
	return PixelCollision(_Collision->GetTransform(), Precission_coefficient);
}
