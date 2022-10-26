#include "PreCompile.h"
#include "GameEngineThreadQueue.h"
#include "GameEngineDebug.h"

GameEngineThreadQueue::GameEngineThreadQueue(const std::string& _ThreadName, int _ThreadCount)
{
	ThreadCount_ = _ThreadCount;

	if (ThreadCount_ == 0)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		ThreadCount_ = Info.dwNumberOfProcessors - 2;
	}

	if (ThreadCount_ <= 0)
	{
		ThreadCount_ = 1;
	}

	if (false == Iocp.Start(ThreadCount_))
	{
		GameEngineDebug::MsgBoxError("GameEngineIOCP 초기화 오류");
	}

	for (size_t i = 0; i < ThreadCount_; i++)
	{
		GameEngineThread* NewThread = new GameEngineThread();
		std::string ThreadName = _ThreadName + std::to_string(static_cast<int>(i));
		NewThread->Start(ThreadName, std::bind(JobWorkThread, NewThread, &Iocp));
		Threads_.push_back(NewThread);
	}
}

void GameEngineThreadQueue::JobPost(std::function<void()> _Job)
{
	Job* NewJob = new Job();
	NewJob->JobFunction = _Job;
	Iocp.Makework(-2, NewJob);
}

void GameEngineThreadQueue::JobWorkThread(GameEngineThread* Thread, GameEngineIocp* _Iocp)
{
	DWORD lpNumberOfBytesTransferred = 0;
	ULONG_PTR lpCompletionKey = 0;
	LPOVERLAPPED Ptr = nullptr;

	//IOCP가 반환해 주는 값에따라 스레드를 계속 작동할지, 중간에 폐기할지 결정한다.

	while (true)
	{
		_Iocp->WaitforWork(lpNumberOfBytesTransferred, lpCompletionKey, Ptr);

		switch (lpNumberOfBytesTransferred)
		{
		case -1:
		{
			return;
		}
		case -2:
		{
			Job* PostJob = reinterpret_cast<Job*>(lpCompletionKey);
			PostJob->JobFunction();
			delete PostJob;
			break;
		}
		default:
			break;
		}
	}
}

void GameEngineThreadQueue::Destroy()
{
	for (size_t i = 0; i < ThreadCount_; i++)
	{
		Iocp.Makework(-1, nullptr);
		Sleep(1);
	}

	for (size_t i = 0; i < Threads_.size(); i++)
	{
		delete Threads_[i];
		Threads_[i] = nullptr;
	}

	Threads_.clear();
}

GameEngineThreadQueue::~GameEngineThreadQueue()
{
	Destroy();
}