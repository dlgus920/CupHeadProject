#pragma once
#include "GameEngineSound.h"

// �з� :
// �뵵 :
// ���� :
class GameEngineSoundPlayer
{
	friend GameEngineSoundManager;

private:	// member Var
	GameEngineSoundManager* playSoundFile_;
	FMOD::Channel* playChannel_; // 
	int PlayCount;
	float Volume_;
	bool* flag_;

private:		
	GameEngineSoundPlayer(); // default constructer ����Ʈ ������
	~GameEngineSoundPlayer(); // default destructer ����Ʈ �Ҹ���

	GameEngineSoundPlayer(const GameEngineSoundPlayer& _other) = delete; 
	GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept; 
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer& _other) = delete; 
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer&& _other) = delete; 

public:		
	bool IsPlay();
	void PlayCountReset(int _Count = -1);
	void PlayOverLap(const std::string& _name, int _LoopCount = 0);
	void PlayAlone(const std::string& _name, int _LoopCount = 0);

	void PlayLevelOverLap(const std::string& _name, int _LoopCount = 0);

	void SetVolume(float _volume);
	void AdjustVolume(float _volume);

	void Stop();

	const float Getvolume()
	{
		float vol = 0;
		playChannel_->getVolume(&vol);

		return vol;
	}

public:
	
};

