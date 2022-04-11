#pragma once
#include "UIBase.h"

class Bottom_HP : public UIBase
{
public:
	Bottom_HP();
	~Bottom_HP();

private:		
	Bottom_HP(const Bottom_HP& _other) = delete;
	Bottom_HP(Bottom_HP&& _other) = delete;
	Bottom_HP& operator=(const Bottom_HP& _other) = delete;
	Bottom_HP& operator=(const Bottom_HP&& _other) = delete;

private:
	GameEngineImageRenderer* UIRenderer_;
	Player* Player_;

	// ������ �� ��� ������ �ﰢ������ ó��

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;
};

