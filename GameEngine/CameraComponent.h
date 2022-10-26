#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineDebugRenderData.h"
#include "Enums.h"

// 투영 타입
enum class ProjectionMode
{
	Perspective,
	Orthographic
};

class GameEngineRenderer;
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;
	friend class GameEngineLevel;

private:	
	ProjectionMode				ProjectionMode_;			// 
	float						FovAngleY_;					// 
	float4						CamSize_;					// 
	float						NearZ_;						// 
	float						FarZ_;						// 
	float						ZoomValue;

	int DebugRenderCount_;
	float ZoomValue_;

	std::map<int, std::list<GameEngineRenderer*>> RendererList_;
	std::vector<GameEngineDebugRenderData> DebugVector_;

	GameEngineRenderTarget* CameraBufferTarget_;

private:
	void ClearCameraTarget();
	void CameraTransformUpdate();
	void Render();
	void DebugRender();
	void ReleaseRenderer();

public:
	void CameraZoomReset();
	void CameraZoomSetting(float _Value);

	void SetProjectionMode(ProjectionMode _ProjectionMode);
	void PushRenderer(int _Order, GameEngineRenderer* _Renderer);

	void PushDebugRender(GameEngineTransform* _Trans, CollisionType _Type, float4 _Color);
	void ChangeRendererGroup(int _Group, GameEngineRenderer* _Renderer);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline GameEngineRenderTarget* GetCameraRenderTarget()
	{
		return CameraBufferTarget_;
	}

	inline float GetZoomValue()
	{
		return ZoomValue_;
	}

public:
	CameraComponent();
	~CameraComponent();

protected:		
	CameraComponent(const CameraComponent& _other) = delete;
	CameraComponent(CameraComponent&& _other) noexcept = delete;

private:		
	CameraComponent& operator=(const CameraComponent& _other) = delete;
	CameraComponent& operator=(const CameraComponent&& _other) = delete;
};

