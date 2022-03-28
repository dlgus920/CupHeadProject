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

void Map::SetMapImage(std::string _MapImage, std::string _CollisionMap, float Pivot_x, float Pivot_y)
{
	{
		MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		MapImage_->SetImage(_MapImage);
		MapImage_->SetAdjustImzgeSize();
		//MapImage_->GetTransform()->SetWorldPosition(float4{ Pivot_x, Pivot_y, static_cast<int>(ZOrder::Z03Map00) });
		//MapImage_->GetTransform()->SetLocalPosition(float4{ Pivot_x, Pivot_y, static_cast<int>(ZOrder::Z03Map00) });
	}

	{
		CollisionMap_ = CreateTransformComponent<GameEngineImageRenderer>();
		CollisionMap_->SetImage(_CollisionMap);
		CollisionMap_->SetAdjustImzgeSize();
		//CollisionMap_->GetTransform()->SetWorldPosition(float4{ Pivot_x, Pivot_y, static_cast<int>(ZOrder::Z04CollisonMap00) });
		//CollisionMap_->GetTransform()->SetLocalPosition(float4{ Pivot_x, Pivot_y, static_cast<int>(ZOrder::Z04CollisonMap00) });
	}
	
		GetTransform()->SetWorldPosition(float4{ Pivot_x, Pivot_y, static_cast<int>(ZOrder::Z04CollisonMap00) });

	//GetTransform()->SetWorldPosition(Pivot_x, Pivot_y);
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
	//TODO : ÀÌ»õ³¢°¡ ¾ò¾î¿Ã ÇÈ¼¿ÀÇ ÁÂÇ¥¸¦ ¾îÂ¼±¸ ÀúÂ¼±¸
	return CurrentMap->CollisionMap_->GetCurrentTexture()->GetPixel(_Postion.ix(), _Postion.iy());
}