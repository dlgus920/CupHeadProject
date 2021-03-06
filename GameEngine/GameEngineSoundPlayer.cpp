#include "PreCompile.h"
#include "GameEngineSoundPlayer.h"
#include "GameEngineSound.h"


// Static Var
// Static Func

// constructer destructer
GameEngineSoundPlayer::GameEngineSoundPlayer()
	: playSoundFile_(nullptr)
	, playChannel_(nullptr)
	, flag_(nullptr)
	, PlayCount(-1)
	, Volume_(1.f)
{
}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{
}

GameEngineSoundPlayer::GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept
	: playSoundFile_(_other.playSoundFile_)
	, playChannel_(_other.playChannel_)
{
}

//member Func

bool GameEngineSoundPlayer::IsPlay() 
{
	bool Check = false;
	// 이 FMOD를 짠사람이 그냥 이렇게 짠거에요.
	playChannel_->isPlaying(&Check);
	return Check;
}

void GameEngineSoundPlayer::PlayCountReset(int _Count /*= -1*/) 
{
	PlayCount = _Count;
}

void GameEngineSoundPlayer::PlayOverLap(const std::string& _name, int _LoopCount/* = 1*/)
{
	GameEngineSound* SoundPtr = GameEngineSoundManager::GetInst().FindSound(_name);
#ifdef _DEBUG
	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}
#endif // _DEBUG

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);
	
}

void GameEngineSoundPlayer::PlayAlone(const std::string& _name, int _LoopCount /*= 1*/) 
{
	// 함수를 만들어서 그함수를 다시 실행
	GameEngineSound* SoundPtr = GameEngineSoundManager::GetInst().FindSound(_name);
#ifdef _DEBUG
	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}
#endif // _DEBUG

	if (true == IsPlay())
	{
		return;
	}

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);
}

void GameEngineSoundPlayer::PlayLevelOverLap(const std::string& _name, int _LoopCount)
{
	GameEngineSound* SoundPtr = GameEngineSoundManager::GetInst().FindSoundLevelRes(_name);
#ifdef _DEBUG
	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}
#endif // _DEBUG

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);

	playChannel_->setVolume(GameEngineSoundManager::globalVolume_ * Volume_);
}

void GameEngineSoundPlayer::Stop()
{
	if (nullptr == playChannel_)
	{
		return;
	}

	playChannel_->stop();
	playChannel_ = nullptr;
}

void GameEngineSoundPlayer::SetVolume(float _volume)
{
	Volume_ = _volume;

	//if (playChannel_ != nullptr)
	//{
	//	FMOD_RESULT result = playChannel_->setVolume(GameEngineSoundManager::globalVolume_ * _volume);
	//}
	playChannel_->setVolume(GameEngineSoundManager::globalVolume_ * Volume_);
}

void GameEngineSoundPlayer::AdjustVolume(float _volume)
{
	Volume_ += _volume;

	playChannel_->setVolume(GameEngineSoundManager::globalVolume_ * Volume_);
}
