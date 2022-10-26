#pragma once

// 설명 : 
class GameEngineRenderingPipeLine;
class GameEngineRenderingPipeLineManager
{
private:
	static GameEngineRenderingPipeLineManager* Inst;

private:
	std::map<std::string, GameEngineRenderingPipeLine*> ResourcesMap;

public:
	GameEngineRenderingPipeLine* Create(const std::string& _Name);
	// 파일에서 로드
	GameEngineRenderingPipeLine* Load(const std::string& _Path);
	// 이름 직접 지정
	GameEngineRenderingPipeLine* Load(const std::string& _Name, const std::string& _Path);
	// 목록에서 찾는다.
	GameEngineRenderingPipeLine* Find(const std::string& _Name);

public:
	static GameEngineRenderingPipeLineManager& GetInst()
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

private:
	GameEngineRenderingPipeLineManager(); // default constructer 디폴트 생성자
	~GameEngineRenderingPipeLineManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderingPipeLineManager(const GameEngineRenderingPipeLineManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderingPipeLineManager(GameEngineRenderingPipeLineManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderingPipeLineManager& operator=(const GameEngineRenderingPipeLineManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderingPipeLineManager& operator=(const GameEngineRenderingPipeLineManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
};




