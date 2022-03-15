#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine\EngineVertex.h>
#include "UserGame_Resources_Shader.h"


void UserGame::ResourcesLoad()
{
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

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}	
		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Animation.png");
		Texture->Cut(8, 9);
	}
	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent(GV_GAMEFILENAME);
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("TitleScreen");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}
		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("title_screen_background.png");
		Texture->Cut(8, 8);
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
		Texture->Cut(200.f, 320.f);
		
	}

	AppShaderLoad(); //TODO : 현재 문제 발생 주범

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Color");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");
		Pipe->SetVertexShader("Color_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Color_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Texture");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Texture_VS");
		Pipe->SetVertexShader("Texture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Texture_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}

}


//#include "PreCompile.h"
//#include "UserGame.h"
//#include <GameEngine\EngineVertex.h>
//#include "UserGame_Resources_Shader.h"
//
//
//void UserGame::ResourcesLoad()
//{
//	{
//		GameEngineDirectory SoundDir;
//		SoundDir.MoveParent("CupHeadProject");
//		SoundDir.MoveChild("Resources");
//		SoundDir.MoveChild("Sound");
//
//		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");
//
//		for (size_t i = 0; i < AllFile.size(); i++)
//		{
//			GameEngineSoundManager::GetInst().Load(AllFile[i].GetFullPath());
//		}
//	}
//
//	{
//		GameEngineDirectory TextureDir;
//		TextureDir.MoveParent("CupHeadProject");
//		TextureDir.MoveChild("Resources");
//		TextureDir.MoveChild("Image");
//
//		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();
//
//		for (size_t i = 0; i < AllFile.size(); i++)
//		{
//			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
//		}
//	}
//
//	GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("Animation.png");
//	Texture->Cut(8, 8);
//
//	{
//		GameEngineDirectory TextureDir;
//		TextureDir.MoveParent("CupHeadProject");
//		TextureDir.MoveChild("Resources");
//		TextureDir.MoveChild("Image");
//
//		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Dash"));
//	}
//
//
//
//
//	AppShaderLoad();
//
//
//
//	{
//		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Color");
//		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
//		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");
//		Pipe->SetVertexShader("Color_VS");
//		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
//		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//		Pipe->SetRasterizer("EngineBaseRasterizer");
//		Pipe->SetPixelShader("Color_PS");
//		Pipe->SetOutputMergerBlend("AlphaBlend");
//	}
//
//	{
//		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Texture");
//		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
//		Pipe->SetInputAssembler1InputLayOutSetting("Texture_VS");
//		Pipe->SetVertexShader("Texture_VS");
//		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
//		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//		Pipe->SetRasterizer("EngineBaseRasterizer");
//		Pipe->SetPixelShader("Texture_PS");
//		Pipe->SetOutputMergerBlend("AlphaBlend");
//	}
//
//}
