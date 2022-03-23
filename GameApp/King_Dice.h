#pragma once
#include "Monster.h"

// 분류 : 
// 용도 : 
// 설명 : 
class King_Dice : public Monster
{
public:
	King_Dice(); // default constructer 디폴트 생성자
	~King_Dice(); // default destructer 디폴트 소멸자

	King_Dice(const King_Dice& _other) = delete; // default Copy constructer 디폴트 복사생성자
	King_Dice(King_Dice&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	King_Dice& operator=(const King_Dice& _other) = delete; // default Copy operator 디폴트 대입 연산자
	King_Dice& operator=(const King_Dice&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;
public:
};

