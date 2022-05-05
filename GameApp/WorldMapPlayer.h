#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineFSM.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "Image.h"
#include "Map.h"
#include "StagePoint.h"

class GameEngineImageRenderer;

enum class AnimationDirection
{
	Right,
	Left,
};

class WorldMapPlayer : public GameEngineActor
{
	friend class WorldMapScene;
	friend class GameEngineLevel;

private:
	WorldMapPlayer(); // default constructer ����Ʈ ������
	~WorldMapPlayer(); // default destructer ����Ʈ �Ҹ���

	WorldMapPlayer(const WorldMapPlayer& _other) = delete; // default Copy constructer ����Ʈ ���������
	WorldMapPlayer(WorldMapPlayer&& _other) noexcept  = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	WorldMapPlayer& operator=(const WorldMapPlayer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WorldMapPlayer& operator=(const WorldMapPlayer&& _other) noexcept  = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:	// member Var
	GameEngineImageRenderer* PlayerImageRenderer;
	GameEngineCollision* PlayerCollision;
	GameEngineFSM<WorldMapPlayer> State_;

	float TimeCheck_;

	float4 MoveDir_;

	std::string CurState_;

	bool KeyState_Update_;
	bool ColState_Update_;
	bool State_Update_;

	bool KeyState_Up_;
	bool KeyState_Down_;
	bool KeyState_Left_;
	bool KeyState_Right_;

	bool KeyState_Chose_;


	//bool ColState_;

	bool4 ColState_;
	class StagePoint* ColState_Chose_;
	//bool AniState_ScreenIris_End_;

	AnimationDirection		Dir_; // �����ִ� ����, ������ ����

private: //Legacy
	void Start() override;
	void Update(float _DeltaTime) override;

private: //Setting
	void KeySetting();
	void StateSetting();
	void ComponentSetting();
	void AnimationSetting();

private: //Update
	void StateUpdate(float _DeltaTime);
	void KeyUpdate();
	void CollisonUpdate();

private: // Func

	std::string CheckState();
	void Move(float4 MoveDir, float _DeltaTime);
	void Move(float DirX, float DirY, float _DeltaTime);

	void SetChangeAnimation(std::string _animation);

	void ChangeScene(std::string _Scene);

	void EffectDust();

public:
	void Entry();

private:
	void Entry_Start();
	void Entry_Update( float _DeltaTime);
	void Entry_End();

	void Idle_Start();
	void Idle_Update( float _DeltaTime);
	void Idle_End();

	void Walk_Start();
	void Walk_Update( float _DeltaTime);
	void Walk_End();

	void Chose_Start();
	void Chose_Update( float _DeltaTime);
	void Chose_End();

};

