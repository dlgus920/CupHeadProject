#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class Player_Update
{
private:	// member Var

public:
	Player_Update(); // default constructer 디폴트 생성자
	~Player_Update(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Player_Update(const Player_Update& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Player_Update(Player_Update&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Player_Update& operator=(const Player_Update& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Player_Update& operator=(const Player_Update&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

