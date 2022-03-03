#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class EffectBase : public GameEngineActor
{
private:	// member Var

public:
	EffectBase(); // default constructer ����Ʈ ������
	~EffectBase(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	EffectBase(const EffectBase& _other) = delete; // default Copy constructer ����Ʈ ���������
	EffectBase(EffectBase&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	EffectBase& operator=(const EffectBase& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EffectBase& operator=(const EffectBase&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);
	virtual void ReleaseEvent();
};

