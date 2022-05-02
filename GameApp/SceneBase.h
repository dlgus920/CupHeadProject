#pragma once
#include <GameEngine/GameEngineLevel.h>

class SceneBase : public GameEngineLevel
{
private:	// member Var

public:
	SceneBase();
	~SceneBase();

	SceneBase(const SceneBase& _other) = delete;
	SceneBase(SceneBase&& _other) = delete;
	SceneBase& operator=(const SceneBase& _other) = delete;
	SceneBase& operator=(const SceneBase&& _other) = delete;

	class Image* FadeImage_;
	float TimeCheck_;
	float BlendRate_;

private:
	//std::map<std::string, GameEngineFolderTexture*> FolderResourcesMap;
	//std::map<std::string, GameEngineTexture*> TextureResourcesMap;

protected:
	class Player* Player_;
	bool Victory_;

private:

protected:
	//GameEngineTexture* SceneTextureLoad(const std::string& _Path);
	//// �̸� ���� ����
	//GameEngineTexture* SceneTextureLoad(const std::string& _Name, const std::string& _Path);
	//// ��Ͽ��� ã�´�.
	//GameEngineTexture* SceneTextureFind(const std::string& _Name);

	void PlayerResourceLoad();
	void SceneResourceLoad();
	//void SceneResourceClear();
public:
	void Knockout();
	void ReadyWALLOP();
	void KnockoutEnd();

protected:
	virtual void LevelResourcesLoad();
	virtual void LevelStart();
	virtual void LevelUpdate(float _DeltaTime);

	virtual void LevelChangeEndEvent();
	virtual void LevelChangeStartEvent();

protected:


};

