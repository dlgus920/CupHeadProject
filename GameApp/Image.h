#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImageRenderer;

class Image : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* ImageRenderer;
public:
	Image(); // default constructer ����Ʈ ������
	~Image(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Image(const Image& _other) = delete; // default Copy constructer ����Ʈ ���������
	Image(Image&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Image& operator=(const Image& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Image& operator=(const Image&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

	void SetImage(std::string _name)
	{
		ImageRenderer->SetImage(_name);
	}
};

