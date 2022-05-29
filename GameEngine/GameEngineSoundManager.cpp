#include "PreCompile.h"
#include "GameEngineSound.h"
#include "GameEngineLevel.h"
#include "GameEngineCore.h"
#include "GameEngineSoundPlayer.h"


GameEngineSoundManager* GameEngineSoundManager::Inst = new GameEngineSoundManager();
std::mutex GameEngineSoundManager::ManagerLock;

float GameEngineSoundManager::globalVolume_ = 1.0f;

GameEngineSoundManager::GameEngineSoundManager()
{
}

GameEngineSoundManager::~GameEngineSoundManager()
{
	{
		std::list<GameEngineSoundPlayer*>::iterator StartIter = allSoundPlayer_.begin();
		std::list<GameEngineSoundPlayer*>::iterator EndIter = allSoundPlayer_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != *StartIter)
			{
				delete *StartIter;
			}
		}
		allSoundPlayer_.clear();
	}

	{
		std::map<std::string, GameEngineSound*>::iterator StartIter = allLoadSound_.begin();
		std::map<std::string, GameEngineSound*>::iterator EndIter = allLoadSound_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
		allLoadSound_.clear();
	}

	std::map< GameEngineLevel*, std::map<std::string, GameEngineSound*>>::iterator iter0 = GlobalResourcesMap.begin();
	std::map< GameEngineLevel*, std::map<std::string, GameEngineSound*>>::iterator iter1 = GlobalResourcesMap.end();

	for (; iter0 != iter1; ++iter0)
	{
		for (const std::pair<std::string, GameEngineSound*>& Res : iter0->second)
		{
			if (nullptr != Res.second)
			{
				delete Res.second;
			}
		}
	}

	GlobalResourcesMap.clear();


	if (nullptr != soundSystem_)
	{
		soundSystem_->release();
		soundSystem_ = nullptr;
	}
}

GameEngineSound* GameEngineSoundManager::FindSound(const std::string& _name)
{
	std::map<std::string, GameEngineSound*>::iterator FindIter = allLoadSound_.find(_name);

	if (FindIter == allLoadSound_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSoundManager::SoundUpdate() 
{
#ifdef _DEBUG
	if (nullptr == soundSystem_)
	{
		GameEngineDebug::MsgBoxError("SoundSystem Is null");
		return;
	}
#endif // _DEBUG

	soundSystem_->update();
}

GameEngineSoundPlayer* GameEngineSoundManager::CreateSoundPlayer()
{
	GameEngineSoundPlayer* NewSoundplayer = new GameEngineSoundPlayer();

	allSoundPlayer_.push_back(NewSoundplayer);

	return  NewSoundplayer;
}

void GameEngineSoundManager::Load(const std::string& _path) 
{
	Load(GameEnginePath::GetFileName(_path), _path);
}
void GameEngineSoundManager::Load(const std::string& _name, const std::string& _path)
{
#ifdef _DEBUG
	if (nullptr != FindSound(_name))
	{
		GameEngineDebug::MsgBoxError("Sound Load overlap error");
		return;
	}
#endif // _DEBUG

	GameEngineSound* newLoadSound = new GameEngineSound();

	if (false == newLoadSound->Load(_path))
	{
		GameEngineDebug::MsgBoxError("Sound Load Error");
		delete newLoadSound;
		return;
	}

	allLoadSound_.insert(std::map<std::string, GameEngineSound*>::value_type(_name, newLoadSound));
}

GameEngineSound* GameEngineSoundManager::FindSoundLevelRes(const std::string& _name)
{
	std::string UpName = GameEngineString::toupper(_name);

	std::map<std::string, GameEngineSound*>::iterator FindIter;
	std::map<GameEngineLevel*, std::map<std::string, GameEngineSound*>>::iterator FindIterglobal;

	{
		std::lock_guard Lock(ManagerLock);
		FindIterglobal = GlobalResourcesMap.find(GameEngineCore::CurrentLevel());
	}

	if (FindIterglobal == GlobalResourcesMap.end())
	{
		return nullptr;
	}

	{
		std::lock_guard Lock(ManagerLock);
		FindIter = FindIterglobal->second.find(UpName);
	}

	if (FindIter != FindIterglobal->second.end())
	{
		return FindIter->second;
	}

	return nullptr;
}
void GameEngineSoundManager::LoadLevelRes(const std::string& _path)
{
	LoadLevelRes(GameEngineString::toupper(GameEnginePath::GetFileName(_path)), _path);
}
void GameEngineSoundManager::LoadLevelRes(const std::string& _name, const std::string& _path)
{
	std::string UpName = GameEngineString::toupper(_name);
	GameEngineLevel* Level = GameEngineCore::CurrentLevel();

#ifdef _DEBUG
	if (nullptr != FindSoundLevelRes(UpName))
	{
		GameEngineDebug::MsgBoxError(UpName + " Is Overlap Load");
	}
#endif // _DEBUG

	GameEngineSound* NewRes = new GameEngineSound();

	if (false == NewRes->Load(_path))
	{
		GameEngineDebug::MsgBoxError("Sound Load Error");
		delete NewRes;
		return;
	}

	NewRes->SetName(UpName);
	NewRes->Load(_path);
	{
		std::lock_guard Lock(ManagerLock);

		std::map<GameEngineLevel*, std::map<std::string, GameEngineSound*>>::iterator FindIterglobal = GlobalResourcesMap.find(Level);

		if (FindIterglobal == GlobalResourcesMap.end())
		{
			std::map<std::string, GameEngineSound*> FindIter;

			FindIter.insert(std::make_pair(UpName, NewRes));

			GlobalResourcesMap.insert(std::make_pair(Level, FindIter));

			return;
		}

		FindIterglobal->second.insert(std::map<std::string, GameEngineSound*>::value_type(UpName, NewRes));
	}
	return;
}

void GameEngineSoundManager::SetGlobalVolume(float _volume)
{
	if (_volume <= 1.0f)
	{
		globalVolume_ = _volume;
	}
	else
	{
		globalVolume_ = 1.0f;
	}

	//int channels = 0;
	//int realChannels = 0;
	//system_->getChannelsPlaying(&channels, &realChannels);

	FMOD::ChannelGroup* cg;
	soundSystem_->getMasterChannelGroup(&cg);

	int numChannels;
	cg->getNumChannels(&numChannels);

	for (int i = 0; i < numChannels; i++)
	{
		FMOD::Channel* channel = nullptr;
		cg->getChannel(i, &channel);
		if (nullptr != channel)
		{
			channel->setVolume(globalVolume_);
		}
	}

	cg->release();
}


void GameEngineSoundManager::PlaySoundOneShot(const std::string& _name) 
{
	GameEngineSound* SoundPtr = FindSound(_name);
#ifdef _DEBUG
	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}
#endif // _DEBUG

	soundSystem_->playSound(SoundPtr->sound_, nullptr, false, nullptr);
}

//allSoundChannel_

GameEngineSoundPlayer* GameEngineSoundManager::CreateSoundChannel(std::string ChannelName)
{
	GameEngineSoundPlayer* NewSoundplayer = new GameEngineSoundPlayer();

	allSoundChannel_.insert(std::make_pair(ChannelName, NewSoundplayer));

	return  NewSoundplayer;
}

GameEngineSoundPlayer* GameEngineSoundManager::FindSoundChannel(std::string ChannelName)
{
	GameEngineSoundPlayer* find = allSoundChannel_.find(ChannelName)->second;

	if (find == nullptr)
	{
		GameEngineDebug::MsgBoxError("사운드 채널이 없음");
		return nullptr;
	}

	return find;
}

void GameEngineSoundManager::PlaySoundChannel(std::string ChannelName)
{
	GameEngineSoundPlayer* find = allSoundChannel_.find(ChannelName)->second;

	if (find == nullptr)
	{
		GameEngineDebug::MsgBoxError("사운드 채널이 없음");
		return;
	}

	find->PlayLevelOverLap(ChannelName);
}

void GameEngineSoundManager::Initialize()
{
	// 내부코드에서 NEW를 할 가능성이 매우 다분해.
	FMOD::System_Create(&soundSystem_);
#ifdef _DEBUG
	if (nullptr == soundSystem_)
	{
		GameEngineDebug::MsgBoxError("sound system create Error");
		return;
	}
#endif // _DEBUG

	// 동시에 32개 개수인지 사운드 채널의 의미인지를 잘 모르고 있습니다.
	// 32채널을 재생할수 있다는 의미인데 선생님도 잘 모릅니다.
	if (FMOD_OK != soundSystem_->init(32, FMOD_DEFAULT, nullptr))
	{
		GameEngineDebug::MsgBoxError("sound system init Error");
		return;
	}
}
