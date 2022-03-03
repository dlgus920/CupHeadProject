#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� :
class LoaddingScene : public GameEngineLevel
{
private:	// member Var
	std::string PrevScene_;
	std::string NextScene_;

	GameEngineLevel* pPrevScene_;
	GameEngineLevel* pNextScene_;

public:
	LoaddingScene(); // default constructer ����Ʈ ������
	~LoaddingScene(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LoaddingScene(const LoaddingScene& _other) = delete; // default Copy constructer ����Ʈ ���������
	LoaddingScene(LoaddingScene&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LoaddingScene& operator=(const LoaddingScene& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LoaddingScene& operator=(const LoaddingScene&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};

