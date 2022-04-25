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

void UserGame::ResourcesLoad()
{
	GameEngineFontManager::GetInst().Load("궁서");

	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParent(GV_GAMEFILENAME);
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().Load(AllFile[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Effect");


		//std::vector<GameEngineDirectory> AllDir = TextureDir.GetAllDirectoryRecursive();
		//LoadingFolder = static_cast<int>(AllDir.size());

		//for (size_t i = 0; i < AllDir.size(); i++)
		//{
		//	GameEngineCore::ThreadQueue.JobPost(std::bind(TextureLoading, AllDir[i]));
		//}

		/*
		
			static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		CreateActorLevel();
		CreateActorCheck = true;
	}

	playlevel에 이런 조건을 걸어줘서 리소스 로드가 되었는가 체크해야함
		*/



		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("ScreenFx"));
	}

	AppShaderLoad(); //TODO : 현재 문제 발생 주범
}