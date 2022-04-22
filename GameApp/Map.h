#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
class GameEngineImageRenderer;
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	//GameEngineImageRenderer* MapImage_;

private:
	static Map* CurrentMap;
	GameEngineImageRenderer* CollisionMap_;

private:
	static float4 GetColor(GameEngineTransform* _Ptr, bool YRevers = true);

	static float4 GetColor(float4 _Postion);
	static float4 GetColor(int _Postion_x, int _Postion_y);

	//custom func
	//Precission 계수 만큼 정확한 충돌체크가 가능하지만 느려짐
public:
	static float4 PixelCollisionTransform(GameEngineTransform* _Transform, int Precission_coefficient = 10);
	static float4 PixelCollisionTransform(GameEngineCollision* _Collision, int Precission_coefficient = 10);


protected:
	void Start() override;
	void LevelChangeStartEvent() override;

public:
	class Image* ScreenFx;

public:
	GameEngineImageRenderer* GetCollisionMap()
	{
		return CollisionMap_;
	}
private:
};