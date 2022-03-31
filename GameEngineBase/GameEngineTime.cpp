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

// 시간잴 준비를 한다.
void GameEngineTime::TimeCheckReset()
{
	// window의 힘을 빌었습니다.
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

	if (deltaTime_ > 0.016666666666666)
	{
		deltaTime_ = 0.016666666666666;
	}

#ifdef _DEBUG
	++Frame_;

	CheckTime_ += deltaTime_;

	if (CheckTime_ >= 1.f)
	{
		FPS_ = Frame_;
		Frame_ = 0;
		CheckTime_ = 0;
	}
#endif // _DEBUG

}