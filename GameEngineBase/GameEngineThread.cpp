#include "PreCompile.h"
#include "GameEngineThread.h"
#include <Windows.h>
#include "GameEngineString.h"

void GameEngineThread::GameEngineThreadFunction(GameEngineThread* _Thread, std::string _Name)
{
	std::wstring WName;
	GameEngineString::AnsiToUnicode(_Name, WName);
	SetThreadDescription(GetCurrentThread(), WName.c_str());
	_Thread->ThreadFunction(_Thread);
}

void GameEngineThread::Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _Function)
{
	ThreadFunction = _Function;
	Thread = std::thread(GameEngineThreadFunction, this, _ThreadName);
}

void GameEngineThread::Join()
{
	Thread.join();
}

GameEngineThread::GameEngineThread() 
{
}

GameEngineThread::~GameEngineThread() 
{
	Join();
}

