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
			1. �ֻ����κ��� ������ ���ڸ� �޾ƿ�,
			2. ���� ���ڿ� ������ �̵��� ���ڸ� ���ϸ� ������ �̵���Ŵ
			3. ���� ���ڿ� �̵��� ���ڰ� �������� �̵��� ������ �Ǵ���

			4. �̵� �÷��װ� ������ ȭ��ǥ�� �̵���Ŵ
			5. 
			
			
			*/

			//while (StageNum_ != ObjectiveNum_)
			//{

			//if (true == IsMove_)
			//{
			//	//ȭ��ǥ�κ��� ������ �� ��ŭ �̵��ߴ��� �޾ƿ�
			//	//if(true == CursurMoveEnd)
			//	{
			//		if (StageNum_ != ObjectiveNum_)
			//		{
			//			//���� �� �������� ������ ȭ��ǥ���� �� �����̶�� �޼����� ����
			//		}
			//		else
			//		{
			//			//�������� ������, �� ������ ���� ����
			//			IsMove_ = false;
			//			MoveEnd_ = true;
			//			// King_Dice�� MoveEnd_�� �޾ƿͼ� ���� ������� �ѱ�
			//		}
			//	}
			//}






		//		if (false == IsMove_)
		//		{
		//			StageNum_++;
		//			//1ĭ �̵�
		//			IsMove_ = true; 
		//		}
		//		if (true == IsMove_)
		//		{
		//			//������ �Լ� ����,
		//			// ��ǥ ��ǥ ���� Ȯ��
		//			// ���޽� IsMove_ = false;
		//			//

		//		}

		//		if (true == MoveEnd_)
		//		{

		//		}
		//	//}

		//	if (StageNum_ == ObjectiveNum_)
		//	{
		//		MoveEnd_ = true;
		//		//�ֻ��� ������ �̵��� ��� ����
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

