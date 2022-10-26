#pragma once
#include "GameEngineThread.h"
#include "GameEngineIocp.h"

// Ό³Έν :
class GameEngineThreadQueue
{
private:
	class Job
	{
	public:
		std::function<void()> JobFunction;
	};

private:
	GameEngineIocp Iocp;

	int ThreadCount_;
	std::vector<GameEngineThread*> Threads_;

public:
	static void JobWorkThread(GameEngineThread* Thread, GameEngineIocp* _Iocp);

	void JobPost(std::function<void()> _Job);

	void Destroy();

public:
	GameEngineThreadQueue(const std::string& _ThreadName, int _ThreadCount = 0);
	~GameEngineThreadQueue();
};

