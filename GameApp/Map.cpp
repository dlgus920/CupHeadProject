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

	//ScreenFx = GetLevel()->CreateActor<Image>();
	//ScreenFx->ImageCreateAnimationFolder("ScreenFx", "ScreenFx", 0.04f, true);
	//ScreenFx->GetTransform()->SetWorldPosition(float4(640.f, -360.f, static_cast<int>(ZOrder::Z00Fx01)));
	//ScreenFx->ImageRenderer_->GetTransform()->SetLocalScaling(float4{ 1280.f,720.f,1.f });
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

	////정확도를 위한 끝자리 검사
	//if (GetColor(Rect.right, Rect.top) == float4::BLACK)
	//{
	//	Retern.b_Up = 1;
	//}
	//if (GetColor(Rect.right, Rect.bottom) == float4::BLACK)
	//{
	//	Retern.b_Down = 1;
	//}

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

	////정확도를 위한 끝자리 검사
	//if (GetColor(Rect.left, Rect.top) == float4::BLACK)
	//{
	//	Retern.b_Left = 1;
	//}
	//if (GetColor(Rect.right, Rect.bottom) == float4::BLACK)
	//{
	//	Retern.b_Right = 1;
	//}

	return Retern;
}

bool4 Map::PixelCollisionTransform(GameEngineCollision* _Collision, int Precission_coefficient)
{
	return PixelCollisionTransform(_Collision->GetTransform(), Precission_coefficient);
}
