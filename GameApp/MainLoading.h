#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class MainLoading
{
private:	// member Var

public:
	MainLoading(); // default constructer 디폴트 생성자
	~MainLoading(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	MainLoading(const MainLoading& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MainLoading(MainLoading&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MainLoading& operator=(const MainLoading& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MainLoading& operator=(const MainLoading&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

