#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageRenderer.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameObject : public GameEngineActor
{
private:	// member Var

public:
	GameObject(); // default constructer 디폴트 생성자
	~GameObject(); // default destructer 디폴트 소멸자

private:		//delete operator
	GameObject& operator=(const GameObject& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameObject& operator=(const GameObject&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
	GameObject(const GameObject& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameObject(GameObject&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

protected:
	GameEngineImageRenderer* ImageRenderer;

	virtual void Start();
	virtual void Update(float _DeltaTime);
	virtual void ReleaseEvent();

public:
	inline const float4 GetTextureSize()
	{
		return ImageRenderer->GetTextureSize();
	}

	inline const float4 GetCutSize()
	{
		return ImageRenderer->GetCutData();
	}

	inline const float4 GetTextureScale()
	{
		return ImageRenderer->GetTextureScale();
	}

	
public:
};

