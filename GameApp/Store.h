#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class Store
{
private:	// member Var

public:
	Store(); // default constructer 디폴트 생성자
	~Store(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Store(const Store& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Store(Store&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Store& operator=(const Store& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Store& operator=(const Store&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

