#pragma once
#include "PreCompile.h"
#include "GameEngineDebug.h"
#include "GameEngineObjectNameBase.h"
#include "GameEngineTime.h"
#include <map>


class GameEngineFSM
{
private:
	class State
	{
	public:
		std::string Name_;
		std::function<void()> Start_;
		std::function<void(float)> Update_;
		std::function<void()> End_;

		State(
			std::string _Name,
			std::function<void()> _Start,
			std::function<void(float)> _Update,
			std::function<void()> _End
		)
			: Name_(_Name)
			, Start_(_Start)
			, Update_(_Update)
			, End_(_End)
		{

		}
	};
private:
	std::map<std::string, State*> AllState_;
	State* Current_;
	State* Next_;

public:
	GameEngineFSM();
	~GameEngineFSM();

	void ChangeState(const std::string& _Name, bool _bForceChange = false);

	void Update(float _Time);

	inline bool IsCurrentState(const std::string& _Name) const
	{
		return Current_->Name_ == _Name;
	}

	State* GetCurrentState()
	{
		return Current_;
	}

public:
	template <typename T>
	void CreateState(
		const std::string& _Name,
		T* objptr,
		void (T::* _Start)(),
		void (T::* _Update)(float),
		void (T::* _End)()
	)
	{
		if (AllState_.end() != AllState_.find(_Name))
		{
			GameEngineDebug::MsgBoxError("이미 존재하는 스테이트를 또 만들려고 했습니다.");
			return;
		}

		std::function<void()> Start = nullptr;
		std::function<void(float)> Update = nullptr;
		std::function<void()> End = nullptr;

		if (_Start != nullptr)
			Start = std::bind(_Start, objptr);

		if (_Update != nullptr)
			Update = std::bind(_Update, objptr, std::placeholders::_1);

		if (_End != nullptr)
			End = std::bind(_End, objptr);

		AllState_.insert(std::map<std::string, State*>::value_type(_Name, new State{ _Name,Start,Update,End }));	
	}

	bool IsCurStateName(const std::string& _Name)
	{
		if (Current_->Name_ == _Name)
		{
			return true;
		}

		return false;
	}

	const std::string GetName()
	{
		return Current_->Name_;
	}

private:
	GameEngineFSM(const GameEngineFSM& _Other) = delete;
	GameEngineFSM(GameEngineFSM&& _Other) = delete;
	GameEngineFSM& operator=(const GameEngineFSM& _Other) = delete;
	GameEngineFSM& operator=(GameEngineFSM&& _Other) = delete;
};