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

	MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
	MapImage_->SetImage(_MapImage);
	MapImage_->SetAdjustImzgeSize();

	CollisionMap_ = CreateTransformComponent<GameEngineImageRenderer>();
	CollisionMap_->SetImage(_CollisionMap);
	CollisionMap_->SetAdjustImzgeSize();

	float4 mapsize = MapImage_->GetCurrentTexture()->GetMetaDataImageSize();

	GetTransform()->SetWorldPosition(float4{ Pivot_x, Pivot_y, static_cast<int>(ZOrder::Z04CollisonMap00) });
}

void Map::SetMapImage(std::string _MapImage, std::string _CollisionMap)
{
	MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
	MapImage_->SetImage(_MapImage);
	MapImage_->SetAdjustImzgeSize();

	CollisionMap_ = CreateTransformComponent<GameEngineImageRenderer>();
	CollisionMap_->SetImage(_CollisionMap);
	CollisionMap_->SetAdjustImzgeSize();

	float4 mapsize = MapImage_->GetCurrentTexture()->GetMetaDataImageSize();

	GetTransform()->SetWorldPosition(float4{ mapsize.x / 2, -mapsize.y / 2, static_cast<int>(ZOrder::Z04CollisonMap00) });
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