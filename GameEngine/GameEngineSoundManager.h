#pragma once
#include <GameEngineBase/FMOD/fmod.hpp>
#include <list>
#include <map>
#include <string>
#include <mutex>

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib") // Release�� ����� �ڵ�����
#else
#pragma comment(lib, "fmod_vc.lib") // Release�� ����� �ڵ�����
#endif

// �̷� ���� �̹��� ���ҽ� ��Ʈ �츮�� �ε��ϰų� 
// �������� �����ų� �ʹ� �����Ƽ� ����ϴ� ���̺귯����

// �ܰ谡 ������ ����.
// �̴ϼȶ����� �Լ��� ã�´�. <= ��κ� �� ���̺귯�� ��ü �Ѱ� �ý��ۿ� ��ü�� �����Ѵ�.
// �������Լ�����.
// �ε� �Լ��� ã�ƾ��Ѵ�.
// �״����� �������̳� ����Լ��� ã�ƾ� �մϴ�.

// �з� :
// �뵵 :
// ���� :
class GameEngineLevel;
class GameEngineSound;
class GameEngineSoundPlayer;
class GameEngineSoundManager
{
	friend GameEngineSound;
	friend GameEngineSoundPlayer;

private:
	GameEngineSoundManager(); // default constructer ����Ʈ ������
	~GameEngineSoundManager(); // default destructer ����Ʈ �Ҹ���

	GameEngineSoundManager(const GameEngineSoundManager& _other) = delete;
	GameEngineSoundManager(GameEngineSoundManager&& _other) = delete;
	GameEngineSoundManager& operator=(const GameEngineSoundManager& _other) = delete;
	GameEngineSoundManager& operator=(const GameEngineSoundManager&& _other) = delete;

private:
	static GameEngineSoundManager* Inst;
	static std::mutex ManagerLock;

	static float globalVolume_;

	FMOD::System* soundSystem_; // Fmod�� �������ִ� �������̽�
	// ���������ϳ��ϳ��� �ƴ϶�
	// fmod�� ����Ҽ� �ִ��� Ȯ�����ְ� ���带 �ε��Ҽ� �ְ� ���ִ� �⺻ �������̽��Դϴ�.
	// �̳༮�� ���� ����� ��������� �ִ� ȯ���̾�� ���带 ����Ҽ� �ֽ��ϴ�.
	std::map<std::string, GameEngineSound*> allLoadSound_;
	std::map<GameEngineLevel*, std::map<std::string, GameEngineSound*>> GlobalResourcesMap; 

	std::list<GameEngineSoundPlayer*> allSoundPlayer_;

	std::map<std::string,GameEngineSoundPlayer*> allSoundChannel_;

private:
	GameEngineSound* FindSound(const std::string& _name);
	GameEngineSound* FindSoundLevelRes(const std::string& _name);

public:
	void Initialize();

	void Load(const std::string& _path);
	void Load(const std::string& _name, const std::string& _path);

	void LoadLevelRes(const std::string& _path);
	void LoadLevelRes(const std::string& _name, const std::string& _path);

	void SetGlobalVolume(float _volume);

	void PlaySoundOneShot(const std::string& _name);

	GameEngineSoundPlayer* CreateSoundPlayer();

	GameEngineSoundPlayer* CreateSoundChannel(std::string ChannelName);
	GameEngineSoundPlayer* FindSoundChannel(std::string ChannelName);
	void PlaySoundChannel(std::string ChannelName);

	void SoundUpdate();

public:
	static GameEngineSoundManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}
};

