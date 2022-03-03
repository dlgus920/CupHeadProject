#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImageRenderer;

class Image : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* ImageRenderer;
public:
	Image(); // default constructer 디폴트 생성자
	~Image(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Image(const Image& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Image(Image&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Image& operator=(const Image& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Image& operator=(const Image&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:

	void SetImage(std::string _name)
	{
		ImageRenderer->SetImage(_name);
	}
};

