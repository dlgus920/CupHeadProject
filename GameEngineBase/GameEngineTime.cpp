#include "PreCompile.h"
#include "GameEngineTime.h"

// Static Var
GameEngineTime* GameEngineTime::Inst = new GameEngineTime();
// Static Func
// constructer destructer
GameEngineTime::GameEngineTime()
{
	TimeCheckReset();
}

GameEngineTime::~GameEngineTime()
{
}

GameEngineTime::GameEngineTime(const GameEngineTime&& _Other)
	: timeCount_(_Other.timeCount_),
	startCheck_(_Other.startCheck_),
	endCheck_(_Other.endCheck_),
	Frame_(0),
	FPS_(0)
{
}

// �ð��� �غ� �Ѵ�.
void GameEngineTime::TimeCheckReset()
{
	// window�� ���� �������ϴ�.
	QueryPerformanceFrequency(&timeCount_);
	QueryPerformanceCounter(&startCheck_);
	QueryPerformanceCounter(&endCheck_);
}

void GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&endCheck_);
	deltaTime_ = static_cast<double>((endCheck_.QuadPart - startCheck_.QuadPart)) / static_cast<double>(timeCount_.QuadPart);
	startCheck_.QuadPart = endCheck_.QuadPart;


	if (deltaTime_ >= 0.1f)
	{
		std::string Text = std::to_string(deltaTime_) + "\n";
		OutputDebugStringA(Text.c_str());
	}

#ifdef _DEBUG
	++Frame_;

	if (deltaTime_ >= 1.f)
	{
		FPS_ = Frame_;
		Frame_ = 0;
	}
#endif // _DEBUG

}