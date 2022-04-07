#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineFSM.h>

class King_Dice : public GameEngineActor
{
public:
	King_Dice(); // default constructer ����Ʈ ������
	~King_Dice(); // default destructer ����Ʈ �Ҹ���

	King_Dice(const King_Dice& _other) = delete; // default Copy constructer ����Ʈ ���������
	King_Dice(King_Dice&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	King_Dice& operator=(const King_Dice& _other) = delete; // default Copy operator ����Ʈ ���� ������
	King_Dice& operator=(const King_Dice&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	GameEngineFSM<King_Dice> State_;
	GameEngineCollision* MonsterHitBox;
	GameEngineCollision* MonsterCollision;
	GameEngineImageRenderer* MonsterImageRenderer;

private:	// member Var
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

