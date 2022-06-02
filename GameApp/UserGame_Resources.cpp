#include "PreCompile.h"
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
	UserGame::LoadingFolder++;
	GameEngineCore::ThreadQueue.JobPost
	(
		[]()
		{
			GameEngineDirectory TextureDir;
			TextureDir.MoveParent(GV_GAMEFILENAME);
			TextureDir.MoveChild("Resources");
			TextureDir.MoveChild("Image");
			TextureDir.MoveChild("CommonImage");
			TextureDir.MoveChild("UI");

			std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

			for (size_t i = 0; i < AllFile.size(); i++)
			{
				GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
			}
			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Bottom_HP.png");
			Texture->Cut(6, 2);

			Texture = GameEngineTextureManager::GetInst().Find("BottomCard_Dia.png");
			Texture->Cut(6, 1);

			Texture = GameEngineTextureManager::GetInst().Find("BottomCard_Spade.png");
			Texture->Cut(6, 1);

			UserGame::LoadingFolder--;
		}
	);


	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("CommonImage");

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
		TextureDir.MoveChild("CommonImage");
		TextureDir.MoveChild("Loading");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}
		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("HourGlass.png");
		Texture->Cut(16, 3);

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("ScreenIris"));
	}
	//AppShaderLoad(); 
}