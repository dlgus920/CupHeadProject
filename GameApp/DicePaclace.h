#pragma once

class DicePaclace : public GameEngineLevel
{
public:
	DicePaclace(); 
	~DicePaclace(); 

protected:		// delete constructer
	DicePaclace(const DicePaclace& _other) = delete; 
	DicePaclace(DicePaclace&& _other) = delete; 
	DicePaclace& operator=(const DicePaclace& _other) = delete; 
	DicePaclace& operator=(const DicePaclace&& _other) = delete; 

private:	// member Var
	class PerryObjectDice* PerryObjectDice_; 
	class King_Dice* King_Dice_;
	class Player* Player_;

private:
	void LevelResourcesLoad() override;
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

public:
};

