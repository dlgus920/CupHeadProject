#pragma once
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineActor.h>


class StagePoint : public GameEngineActor
{
public:
	StagePoint(); // default constructer 디폴트 생성자
	~StagePoint(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	StagePoint(const StagePoint& _other) = delete; // default Copy constructer 디폴트 복사생성자
	StagePoint(StagePoint&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	StagePoint& operator=(const StagePoint& _other) = delete; // default Copy operator 디폴트 대입 연산자
	StagePoint& operator=(const StagePoint&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:	// member Var
	std::string NextScene_;

	GameEngineCollision*		ObjectCollision_;
	GameEngineImageRenderer*	ObjectRenderer_;

public:
	void Start() override;
	void Update(float _DeltaTime) override;

public:

	void SetNextScene(std::string _NextScene)
	{
		NextScene_ = _NextScene;
	}

	GameEngineCollision* GetObjectCollision()
	{
		return ObjectCollision_;
	}

	GameEngineImageRenderer* GetObjectRenderer()
	{
		return ObjectRenderer_;
	}
	const std::string GetNextScene()
	{
#ifdef _DEBUG
		if (NextScene_.empty())
		{
			GameEngineDebug::MsgBoxError("다음씬을 지정하지 않음");
		}
#endif // _DEBUG

		return NextScene_;
	}
};

