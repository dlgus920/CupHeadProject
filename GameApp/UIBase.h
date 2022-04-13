#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageRenderer.h>

// ���� :
class UIBase : public GameEngineActor
{
public:
	// constrcuter destructer
	UIBase();
	~UIBase();

	// delete Function
	UIBase(const UIBase& _Other) = delete;
	UIBase(UIBase&& _Other) noexcept = delete;
	UIBase& operator=(const UIBase& _Other) = delete;
	UIBase& operator=(UIBase&& _Other) noexcept = delete;

protected:
	class Player* Player_;



protected:
	virtual void Start() ;
	virtual void Update(float _DeltaTime) ;

protected:
	void SetUIPlayer(Player* _Player)
	{
		Player_ = _Player;
	}

};

