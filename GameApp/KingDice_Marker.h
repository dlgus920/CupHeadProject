#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImageRenderer;

class KingDice_Marker : public GameEngineActor
{
public:
	KingDice_Marker();
	~KingDice_Marker();

private:		
	KingDice_Marker(const KingDice_Marker& _other) = delete;
	KingDice_Marker(KingDice_Marker&& _other) = delete;
	KingDice_Marker& operator=(const KingDice_Marker& _other) = delete;
	KingDice_Marker& operator=(const KingDice_Marker&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineImageRenderer* NumRenderer_[11];
	GameEngineImageRenderer* ClearRenderer_[11];

public:
	void Clear(int Num);
	void AllClear();
};

