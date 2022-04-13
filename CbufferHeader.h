#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class CbufferHeader
{
private:	// member Var

public:
	CbufferHeader(); // default constructer 디폴트 생성자
	~CbufferHeader(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	CbufferHeader(const CbufferHeader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	CbufferHeader(CbufferHeader&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	CbufferHeader& operator=(const CbufferHeader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	CbufferHeader& operator=(const CbufferHeader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

