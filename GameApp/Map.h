#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
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

	GameEngineImageRenderer* MapImage_;
	GameEngineImageRenderer* CollisionMap_;

	static float4 GetColor(GameEngineTransform* _Ptr, bool YRevers = true);

	static float4 GetColor(float4 _Postion);

protected:

	void Start() override;
	void LevelChangeStartEvent() override;

public:
	void SetMapImage(std::string _MapImage, std::string _CollisionMap, float Pivot_x, float Pivot_y);


private:
	static Map* CurrentMap;
};