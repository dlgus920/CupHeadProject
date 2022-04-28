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

	std::map<std::string, GameEngineFolderTexture*> FolderResourcesMap;
	std::map<std::string, GameEngineTexture*> TextureResourcesMap;

	void Clear()
	{
		FolderResourcesMap.clear();
		TextureResourcesMap.clear();
	}

	GameEngineTexture* SceneTextureLoad(const std::string& _Path);
	// 이름 직접 지정
	GameEngineTexture* SceneTextureLoad(const std::string& _Name, const std::string& _Path);
	// 목록에서 찾는다.
	GameEngineTexture* SceneTextureFind(const std::string& _Name);

public:

protected:
	virtual void LevelResourcesLoad();
	virtual void LevelStart();
	virtual void LevelUpdate(float _DeltaTime);
	virtual void LevelChangeEndEvent();
	virtual void LevelChangeStartEvent();

};

