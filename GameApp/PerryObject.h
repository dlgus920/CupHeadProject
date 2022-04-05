#pragma once
#include "Object.h"

// 분류 : 
// 용도 : 
// 설명 : 
class PerryObject : public Object
{
public:
	PerryObject();
	~PerryObject(); 

	PerryObject(const PerryObject& _other) = delete; 
	PerryObject(PerryObject&& _other) = delete;
	PerryObject& operator=(const PerryObject& _other) = delete; 
	PerryObject& operator=(const PerryObject&& _other) = delete; 

private:	// member Var

public:
	void Start() override;
	void Update(float _DeltaTime) override;
};

