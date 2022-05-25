#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageRenderer.h>

// 설명 :
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

public:
	static UIBase* UIBase_;
	// 딱 1번 만들어지고 오로지 끄고 키고의 기능만 제공할것,
	

private:
	class OldFilrm* OldFilrm_;
	class Bottom_Card* Bottom_Card_;
	class Bottom_HP* Bottom_HP_;
	
	class CameraActor* Camera_;

protected:
	class Player* Player_;

public:
	void TurnOffBotUI();
	void TurnOnBotUI();

	Bottom_Card* GetBottom_Card();
	Bottom_HP* GetBottom_HP();

protected:
	virtual void Start() ;
	virtual void Update(float _DeltaTime) ;

protected:
	void SetUIPlayer(Player* _Player)
	{
		Player_ = _Player;
	}

};

