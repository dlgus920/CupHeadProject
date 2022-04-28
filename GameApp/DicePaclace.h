#pragma once
#include <GameEngineBase/GameEngineFSM.h>
#include "SceneBase.h"

#include <GameEngineBase/GameEngineRandom.h>

class DicePaclace : public SceneBase
{
	friend class LoaddingScene;
public:
	DicePaclace(); 
	~DicePaclace(); 

protected:		// delete constructer
	DicePaclace(const DicePaclace& _other) = delete; 
	DicePaclace(DicePaclace&& _other) = delete; 
	DicePaclace& operator=(const DicePaclace& _other) = delete; 
	DicePaclace& operator=(const DicePaclace&& _other) = delete; 

private:	
	GameEngineFSM<DicePaclace> PhaseState_;
	class GameEngineRandom Random_;

	class King_Dice* King_Dice_;
	class Player* Player_;
	class KingDice_Marker* KingDice_Marker_;

	class Image* ScreenFx;

	std::string NextScene_;

	bool Victory_;

	int StageMoveCount_;
	int CurStageNum_; //max 10
	int NextStageNum_; //max 10

	bool IsStageMove_;
	bool MoveEnd_;

private:
	void LevelResourcesLoad() override;
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

public:
	void Knockout();
	void ReadyWALLOP();
	void KnockoutEnd();

	void SetPlusDiceNum(int _num)
	{
		StageMoveCount_ = _num; 
		IsStageMove_ = true;
		//{
			/*
			1. 주사위로부터 움직일 숫자를 받아옴,
			2. 현재 숫자와 앞으로 이동할 숫자를 비교하며 앞으로 이동시킴
			3. 현재 숫자와 이동할 숫자가 같아지면 이동이 끝났다 판단함

			4. 이동 플레그가 켜지면 화살표를 이동시킴
			5. 
			
			
			*/

			//while (StageNum_ != ObjectiveNum_)
			//{

			//if (true == IsMove_)
			//{
			//	//화살표로부터 정해진 양 만큼 이동했는지 받아옴
			//	//if(true == CursurMoveEnd)
			//	{
			//		if (StageNum_ != ObjectiveNum_)
			//		{
			//			//아직 더 움직여야 함으로 화살표에게 더 움직이라고 메세지를 보냄
			//		}
			//		else
			//		{
			//			//움직임이 끝났음, 더 움직일 곳이 없음
			//			IsMove_ = false;
			//			MoveEnd_ = true;
			//			// King_Dice가 MoveEnd_를 받아와서 다음 페이즈로 넘김
			//		}
			//	}
			//}






		//		if (false == IsMove_)
		//		{
		//			StageNum_++;
		//			//1칸 이동
		//			IsMove_ = true; 
		//		}
		//		if (true == IsMove_)
		//		{
		//			//움직임 함수 시작,
		//			// 목표 좌표 도달 확인
		//			// 도달시 IsMove_ = false;
		//			//

		//		}

		//		if (true == MoveEnd_)
		//		{

		//		}
		//	//}

		//	if (StageNum_ == ObjectiveNum_)
		//	{
		//		MoveEnd_ = true;
		//		//주사위 굴림과 이동이 모두 끝남
		//	}
		//}

	}

private:
	void ResourcesLoading_Start();
	void ResourcesLoading_Update(float _DeltaTime);
	void ResourcesLoading_End();

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Playing_Start();
	void Playing_Update(float _DeltaTime);
	void Playing_End();

	bool ThreadResourceLoad();


public:
	//friend void WorldMapPlayer::ChangeScene(std::string _Scene);

	void SetNextScene(std::string _NextScene)
	{
		NextScene_ = _NextScene;
	}
};

