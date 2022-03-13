#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� :
class LoaddingScene : public GameEngineLevel
{
private:	// member Var
	std::string NextScene_;

	class Image* HourGlass_;

	bool LoadEnd_;
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
public:
	void SetNextLevel(std::string _Nextlevel)
	{
		NextScene_ = _Nextlevel;
	}
};

