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
	class Image* HourGlass_;
	bool Victory_;

	bool LoadingComplete_;
	bool LoadingFadeComplete_;

private:

protected:
	virtual void Init_Update(float _DeltaTime) = 0;

	virtual void ResourcesLoad_Start() = 0;
	virtual void ResourcesLoad_Update(float _DeltaTime) = 0;
	virtual void ResourcesLoad_End() = 0;

	virtual void LevelLoop_Start() = 0;
	virtual void LevelLoop_Update(float _DeltaTime) = 0;
	virtual void LevelLoop_End() = 0;

	//GameEngineTexture* SceneTextureLoad(const std::string& _Path);
	//// 이름 직접 지정
	//GameEngineTexture* SceneTextureLoad(const std::string& _Name, const std::string& _Path);
	//// 목록에서 찾는다.
	//GameEngineTexture* SceneTextureFind(const std::string& _Name);

	void PlayerResourceLoad();
	void SceneResourceLoad();

	void ResourcesLoadFadeInit();
	void LevelLoadFadeUpdate(float _DeltaTime);
	//void ResourcesLoadFadeUpdate(float _DeltaTime);
	//void SceneResourceClear();
public:
	void Knockout();
	void ReadyWALLOP();
	void KnockoutEnd();

protected:
	virtual void LevelStart();
	virtual void LevelUpdate(float _DeltaTime);

	virtual void LevelChangeEndEvent();
	virtual void LevelChangeStartEvent();

protected:


};

