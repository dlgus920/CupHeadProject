#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "Map.h"

Map* Map::CurrentMap = nullptr;

Map::Map()
	: CollisionMap_(nullptr)
{
}

Map::~Map()
{
}

void Map::Start()
{
	CollisionMap_ = CreateTransformComponent<GameEngineImageRenderer>();
}


void Map::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
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
	return CurrentMap->CollisionMap_->GetCurrentTexture()->GetPixel(_Postion.ix(), _Postion.iy());
}

float4 Map::GetColor(int _Postion_x, int _Postion_y)
{
	return CurrentMap->CollisionMap_->GetCurrentTexture()->GetPixel(_Postion_x, _Postion_y);
}

bool4 Map::PixelCollisionTransform(GameEngineTransform* _Transform, int Precission_coefficient/*10*/)
{
	//회전은 고려하지 않음
	//일일이 검사하면 느리니까 한 면을 Precission_coefficient만큼 등분하여 for문으로 검사, 

	float4 size = _Transform->GetLocalScaling(); // ex) 100.f ,100.f;

	float4 Pos = _Transform->GetWorldPosition();
	Pos.y *= -1.0f;

	bool4 Retern;

	// 각각의 4개의 선분의 시작, 종료 지점

  	RECT Rect = {static_cast<int>(Pos.x - size.x / 2)  ,static_cast<int>(Pos.y - size.y / 2),
				 static_cast<int>(Pos.x + size.x / 2) ,static_cast<int>(Pos.y + size.y / 2)};
	
	// 각 가로 세로를 10등분 함

	int HorizenConst = static_cast<int>(size.x / Precission_coefficient);
	int VerticalConst = static_cast<int>(size.y / Precission_coefficient);

	if (HorizenConst < 1)
	{
		HorizenConst = 1;
	}
	if (VerticalConst < 1)
	{
		VerticalConst = 1;
	}

	for (int i = Rect.left + HorizenConst; i < Rect.right; i+= HorizenConst)
	{
		if (GetColor(i, Rect.top) == float4::BLACK)
		{
			Retern.b_Up = true;
		}
		if (GetColor(i, Rect.bottom) == float4::BLACK)
		{
			Retern.b_Down = true;
		}
	}

	for (int i = Rect.top + VerticalConst; i < Rect.bottom; i += VerticalConst)
	{
		if (GetColor(Rect.left, i) == float4::BLACK)
		{
			Retern.b_Left = true;
		}
		if (GetColor(Rect.right, i) == float4::BLACK)
		{
			Retern.b_Right = true;
		}
	}

	return Retern;
}

bool4 Map::PixelCollisionTransform(GameEngineCollision* _Collision, int Precission_coefficient)
{
	return PixelCollisionTransform(_Collision->GetTransform(), Precission_coefficient);
}

bool4 Map::PixelSideCollisionTransform(GameEngineCollision* _Collision, int Precission_coefficient)
{
	GameEngineTransform* _Transform = _Collision->GetTransform();

	float4 size = _Transform->GetLocalScaling(); // ex) 100.f ,100.f;

	float4 Pos = _Transform->GetWorldPosition();
	Pos.y *= -1.0f;

	bool4 Retern;

	RECT Rect = { static_cast<int>(Pos.x - size.x / 2)  ,static_cast<int>(Pos.y - size.y / 2),
				 static_cast<int>(Pos.x + size.x / 2) ,static_cast<int>(Pos.y + size.y / 2) };

	int VerticalConst = static_cast<int>(size.y / Precission_coefficient);

	if (VerticalConst < 1)
	{
		VerticalConst = 1;
	}

	for (int i = Rect.top + VerticalConst; i < Rect.bottom; i += VerticalConst)
	{
		if (GetColor(Rect.left, i) == float4::BLACK)
		{
			Retern.b_Left = true;
		}
		if (GetColor(Rect.right, i) == float4::BLACK)
		{
			Retern.b_Right = true;
		}

		if (Retern.b_Left == Retern.b_Right == true)
		{
			break;
		}
	}

	return Retern;
}

bool Map::PixelUpCollisionTransform(GameEngineCollision* _Collision, int Precission_coefficient)
{
	GameEngineTransform* _Transform = _Collision->GetTransform();

	float4 size = _Transform->GetLocalScaling(); // ex) 100.f ,100.f;

	float4 Pos = _Transform->GetWorldPosition();
	Pos.y *= -1.0f;

	bool4 Retern;

	RECT Rect = { static_cast<int>(Pos.x - size.x / 2)  ,static_cast<int>(Pos.y - size.y / 2),
				 static_cast<int>(Pos.x + size.x / 2) ,static_cast<int>(Pos.y + size.y / 2) };

	int HorizenConst = static_cast<int>(size.x / Precission_coefficient);

	if (HorizenConst < 1)
	{
		HorizenConst = 1;
	}

	for (int i = Rect.left + HorizenConst; i < Rect.right; i += HorizenConst)
	{
		if (GetColor(i, Rect.top) == float4::BLACK)
		{
			return true;
		}
	}

	return false;
}

bool Map::PixelGroundCollisionTransform(GameEngineCollision* _Collision, int Precission_coefficient)
{
	GameEngineTransform * _Transform = _Collision->GetTransform();

	float4 size = _Transform->GetLocalScaling(); 

	float4 Pos = _Transform->GetWorldPosition();
	Pos.y *= -1.0f;

	int HorizenConst = static_cast<int>(size.x / Precission_coefficient);

	if (HorizenConst < 1)
	{
		HorizenConst = 1;
	}

	int Left = static_cast<int>(Pos.x - size.x / 2);
	int Right = static_cast<int>(Pos.x + size.x / 2);
	int Bot = static_cast<int>(Pos.y + size.y / 2);

	for (int i = Left + HorizenConst; i < Right; i += HorizenConst)
	{
		if (GetColor(i, Bot) == float4::BLACK)
		{
			return true;
		}
	}

	return false;
}

bool Map::PixelLeftCollisionTransform(GameEngineCollision* _Collision, int Precission_coefficient)
{
	GameEngineTransform* _Transform = _Collision->GetTransform();

	float4 size = _Transform->GetLocalScaling(); // ex) 100.f ,100.f;

	float4 Pos = _Transform->GetWorldPosition();
	Pos.y *= -1.0f;

	RECT Rect = { static_cast<int>(Pos.x - size.x / 2)  ,static_cast<int>(Pos.y - size.y / 2),
				 static_cast<int>(Pos.x + size.x / 2) ,static_cast<int>(Pos.y + size.y / 2) };

	int VerticalConst = static_cast<int>(size.y / Precission_coefficient);

	if (VerticalConst < 1)
	{
		VerticalConst = 1;
	}

	for (int i = Rect.top + VerticalConst; i < Rect.bottom; i += VerticalConst)
	{
		if (GetColor(Rect.left, i) == float4::BLACK)
		{
			return true;
		}
	}
	return false;
}

bool Map::PixelRightCollisionTransform(GameEngineCollision* _Collision, int Precission_coefficient)
{
	GameEngineTransform* _Transform = _Collision->GetTransform();

	float4 size = _Transform->GetLocalScaling(); // ex) 100.f ,100.f;

	float4 Pos = _Transform->GetWorldPosition();
	Pos.y *= -1.0f;

	RECT Rect = { static_cast<int>(Pos.x - size.x / 2)  ,static_cast<int>(Pos.y - size.y / 2),
				 static_cast<int>(Pos.x + size.x / 2) ,static_cast<int>(Pos.y + size.y / 2) };

	int VerticalConst = static_cast<int>(size.y / Precission_coefficient);

	if (VerticalConst < 1)
	{
		VerticalConst = 1;
	}

	for (int i = Rect.top + VerticalConst; i < Rect.bottom; i += VerticalConst)
	{
		if (GetColor(Rect.right, i) == float4::BLACK)
		{
			return true;
		}
	}
	return false;
}
