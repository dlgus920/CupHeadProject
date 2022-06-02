#pragma once
#include "GameEngineActor.h"
#include "CameraComponent.h"

class CameraComponent;
// Ό³Έν :
class CameraActor : public GameEngineActor
{
public:
	// constrcuter destructer
	CameraActor();
	~CameraActor();

	// delete Function
	CameraActor(const CameraActor& _Other) = delete;
	CameraActor(CameraActor&& _Other) noexcept = delete;
	CameraActor& operator=(const CameraActor& _Other) = delete;
	CameraActor& operator=(CameraActor&& _Other) noexcept = delete;

	CameraComponent* GetCamera() 
	{
		return Camera_;
	}

	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

	bool IsFreeCameraMode();

	void FreeCameraModeSwitch();
	void FreeCameraModeOn();
	void FreeCameraModeOff();


protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);

private:
	GameEngineTransform OriginTransform;
	float FreeCameraSpeed_;
	float RotSpeed_;
	bool IsFreeCameraMode_;
	ProjectionMode PrevCamMode_;
	CameraComponent* Camera_;

	bool IsFixed_;
	float CamSpeed_;
	GameEngineTransform* CamTargetPos_;

	GameEngineLevel* curlevel;

public:
	void SetFixed(bool _IsFixed_)
	{
		IsFixed_ = _IsFixed_;
	}

	void SetCamTargetPos(GameEngineTransform* _CamTargetPos)
	{
		CamTargetPos_ = _CamTargetPos;
	}

	void ResetUpdate()
	{
		if (curlevel == GetLevel())
		{
			CamTargetPos_ = {};
			IsFixed_ = true;
			CamSpeed_ = 100.f;
			curlevel = GetLevel();
		}
	}

	void SetCamSpeed(float _CamSpeed)
	{
		CamSpeed_ = _CamSpeed;
	}

};

