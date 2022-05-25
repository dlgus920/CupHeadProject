#pragma once
#include "UIBase.h"

class OldFilrm : public UIBase
{
public:
	OldFilrm();
	~OldFilrm();

private:
	OldFilrm(const OldFilrm& _other) = delete;
	OldFilrm(OldFilrm&& _other) = delete;
	OldFilrm& operator=(const OldFilrm& _other) = delete;
	OldFilrm& operator=(const OldFilrm&& _other) = delete;

private: 
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	class GameEngineImageRenderer* OldFilrmRenderer_;
};

