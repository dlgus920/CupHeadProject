#include "PreCompile.h"
#include "GameEngineFSM.h"
#include "GameEngineDebug.h"


GameEngineFSM::GameEngineFSM()
	: Current_(nullptr)
	, Next_(nullptr)
{
}

GameEngineFSM::~GameEngineFSM()
{
	for (auto& State : AllState_)
	{
		delete State.second;
		State.second = nullptr;
	}
}

void GameEngineFSM::Update(float _Time)
{
	if (nullptr != Next_)
	{
		if (nullptr != Current_ && nullptr != Current_->End_)
		{
			Current_->End_();
		}
		Current_ = Next_;

		if (nullptr != Current_->Start_)
		{
			Current_->Start_();
		}
		Next_ = nullptr;
	}

	if (nullptr == Current_)
	{
		GameEngineDebug::MsgBoxError("���°� �������� �ʴµ� ���¸ӽ��� �۵���Ű���� �߽��ϴ�.");
		return;
	}

	Current_->Update_(_Time);
}

void GameEngineFSM::ChangeState(const std::string& _Name, bool _bForceChange)
{
	std::map<std::string, State*>::iterator FindIter = AllState_.find(_Name);

	if (AllState_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ������Ʈ�� ü�����Ϸ��� �߽��ϴ�..");
		return;
	}

	Next_ = FindIter->second;
}