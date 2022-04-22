#pragma once
#include "PreCompile.h"
#include "GameEngineDebug.h"
#include "GameEngineObjectNameBase.h"
#include "GameEngineTime.h"
#include <map>

template<typename FSMType>
class GameEngineFSM
{
	class State : public GameEngineObjectNameBase
	{
		friend class GameEngineFSM;

	public:
		GameEngineFSM* parent_;

		void(FSMType::* StateStart)();
		void(FSMType::* StateUpdate)(float DeltaTime);
		void(FSMType::* StateEnd)();

		//std::function<void(void)> UpdateFunc_;
		//std::function<void> StartFunc_;
		//std::function<void> EndFunc_;

	public:

		void CallStart()
		{
			if (nullptr == StateStart)
			{
				return;
			}
#ifdef _DEBUG
			if (nullptr == parent_->ObjectPtr_)
			{
				GameEngineDebug::AssertFalse();
				return;
			}
#endif // _DEBUG
			(parent_->ObjectPtr_->*StateStart)();
		}

		void CallUpdate(float _DeltaTime)
		{
			if (nullptr == StateUpdate)
			{
				return;
			}

#ifdef _DEBUG
			if (nullptr == parent_->ObjectPtr_)
			{
				GameEngineDebug::AssertFalse();
				return;
			}
#endif // _DEBUG

			//void Return = (parent_->ObjectPtr_->*StateUpdate)(_DeltaTime);

			//if (Return._NextState == "")
			//{
			//	return;
			//}

			(parent_->ObjectPtr_->*StateUpdate)(_DeltaTime);
#ifdef _DEBUG
			//if (Return._NextState.size() == 0)
			//{
			//	return;
			//}

			if (nullptr == parent_->FindState(Return._NextState))
			{
				GameEngineDebug::AssertFalse();
			}
#endif // _DEBUG

			
			//parent_->ChangeState(Return._NextState);
		}

		void CallEnd()
		{
			if (nullptr == StateEnd)
			{
				return;
			}

#ifdef _DEBUG
			if (nullptr == parent_->ObjectPtr_)
			{
				GameEngineDebug::AssertFalse();
				return;
			}
#endif // _DEBUG
			(parent_->ObjectPtr_->*StateEnd)();
		}

	public:
		void Update() {}

	public:
		State(GameEngineFSM* _parent)
			: parent_(_parent)
			, StateStart(nullptr)
			, StateUpdate(nullptr)
		{

		}
	};

private:
	std::map<std::string, State*> allState_;
	FSMType* ObjectPtr_;
	State* curState_;
	std::string nextState_;

private:	// member Var

public:
	friend State;

public:
	GameEngineFSM(FSMType* _StateObject)
		: curState_(nullptr)
		, ObjectPtr_(_StateObject)
	{
	}// default constructer 디폴트 생성자

	~GameEngineFSM()
	{
		typename std::map<std::string, State*>::iterator Start = allState_.begin();
		typename std::map<std::string, State*>::iterator End = allState_.end();

		for (; Start != End; ++Start)
		{
			delete Start->second;
		}
		allState_.clear();
	}// default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineFSM(const GameEngineFSM& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineFSM(GameEngineFSM&& _other) noexcept
	{
	}// default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineFSM& operator=(const GameEngineFSM& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineFSM& operator=(const GameEngineFSM&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자



public:
	void CreateState(const std::string& _name, void(FSMType::* _StartFunc)(), void(FSMType::* _UpdateFunc)(float), void(FSMType::* _EndFunc)())
	{
#ifdef _DEBUG
		if (nullptr != FindState(_name))
		{
			GameEngineDebug::AssertFalse();
		}
#endif // _DEBUG
		State* NewState = new State(this);
		NewState->SetName(_name);

		NewState->StateUpdate = _UpdateFunc;
		NewState->StateStart = _StartFunc;
		NewState->StateEnd = _EndFunc;
		allState_.insert(std::map<std::string, State*>::value_type(_name, NewState));
		return;
	}

	void ChangeState(const std::string& _Name)
	{
		if (nullptr != curState_)
		{
			curState_->CallEnd();
		}

		curState_ = FindState(_Name);
#ifdef _DEBUG
		if (nullptr == curState_)
		{
			GameEngineDebug::AssertFalse();
			return;
		}
#endif // _DEBUG

		curState_->CallStart();
	}

	bool IsCurStateName(const std::string& _Name)
	{
		if (nullptr == curState_)
		{
			GameEngineDebug::AssertFalse();
			return false;
		}

		if (curState_->GetName() == _Name)
		{
			return true;
		}

		return false;
	}

	std::string GetName()
	{
		return curState_->GetName();
	}

private:
	State* FindState(const std::string& _name)
	{
		typename std::map<std::string, State*>::iterator FindAniIter = allState_.find(_name);

		if (FindAniIter == allState_.end())
		{
			return nullptr;
		}

		return FindAniIter->second;
	}


public:
	void Update(float _DeltaTime)
	{
#ifdef _DEBUG
		if (nullptr == curState_)
		{
			GameEngineDebug::AssertFalse();
			return;
		}
#endif // _DEBUG

		curState_->CallUpdate(_DeltaTime);
	}
};