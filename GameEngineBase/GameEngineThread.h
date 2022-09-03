#pragma once
#include "GameEngineObjectNameBase.h"
#include <thread>
#include <string>
#include <functional>

class GameEngineThread : public GameEngineObjectNameBase
{
public:
	GameEngineThread();
	~GameEngineThread();

private:
	std::thread Thread;
	std::function<void(GameEngineThread*)> ThreadFunction;

private:
	static void GameServerThreadFunction(GameEngineThread* _Thread, std::string _Name);

public:
	void Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _Function)
	{
		ThreadFunction = _Function;
		Thread = std::thread(GameServerThreadFunction, this, _ThreadName);
	}

	void Join()
	{
		Thread.join();
	}

private:
	GameEngineThread(const GameEngineThread& _Other) = delete;
	GameEngineThread(GameEngineThread&& _Other) = delete;
	GameEngineThread& operator=(const GameEngineThread& _Other) = delete;
	GameEngineThread& operator=(GameEngineThread&& _Other) = delete;
};

