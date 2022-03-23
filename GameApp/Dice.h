#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class Dice
{
private:	// member Var

public:
	Dice(); // default constructer 디폴트 생성자
	~Dice(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Dice(const Dice& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Dice(Dice&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Dice& operator=(const Dice& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Dice& operator=(const Dice&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

