#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageRenderer.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameObject : public GameEngineActor
{
private:	// member Var

public:
	GameObject(); // default constructer ����Ʈ ������
	~GameObject(); // default destructer ����Ʈ �Ҹ���

private:		//delete operator
	GameObject& operator=(const GameObject& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameObject& operator=(const GameObject&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
	GameObject(const GameObject& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameObject(GameObject&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

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

