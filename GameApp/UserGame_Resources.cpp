#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine\EngineVertex.h>
#include "UserGame_Resources_Shader.h"
#include <GameEngine\GameEngineFontManager.h>

void TextureLoading(GameEngineDirectory Dir)
{
	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		// Sleep(10);
	}

	--UserGame::LoadingFolder;
}

void TextureLoading(GameEngineDirectory Dir, int index)
{
	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	GameEngineTextureManager::GetInst().LoadLevelRes(AllFile[index].GetFullPath());
	// Sleep(10);

	--UserGame::LoadingFolder;
}

void TextureLevelLoading(GameEngineDirectory Dir)
{
	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().LoadLevelRes(nullptr, AllFile[i].GetFullPath());
		// Sleep(10);
	}

	--UserGame::LoadingFolder;
}

void UserGame::ResourcesLoad()
{
	GameEngineFontManager::GetInst().Load("±Ã¼­");

	//{
	//	GameEngineDirectory SoundDir;
	//	SoundDir.MoveParent(GV_GAMEFILENAME);
	//	SoundDir.MoveChild("Resources");
	//	SoundDir.MoveChild("Sound");

	//	std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

	//	for (size_t i = 0; i < AllFile.size(); i++)
	//	{
	//		GameEngineSoundManager::GetInst().Load(AllFile[i].GetFullPath());
	//	}
	//}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Effect");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("ScreenFx"));
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Loading");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}
		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("HourGlass.png");
		Texture->Cut(16, 3);
	}
	//AppShaderLoad(); 
}