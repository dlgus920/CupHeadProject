#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineTransformComponent.h"
#include "GameEngineDebugRenderData.h"
#include "Enums.h"

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

public:
	CameraComponent();
	~CameraComponent();
private:
	CameraComponent(const CameraComponent& _Other) = delete;
	CameraComponent(CameraComponent&& _Other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& _Other) = delete;
	CameraComponent& operator=(CameraComponent&& _Other) noexcept = delete;

public:

	void PushRenderer(int _Order, GameEngineRenderer* _Renderer);

	void PushDebugRender(GameEngineTransform* _Trans, CollisionType _Type);

	GameEngineRenderTarget* CameraBufferTarget_;

	void ChangeRendererGroup(int _Group, GameEngineRenderer* _Renderer);

	void SetProjectionMode(ProjectionMode _ProjectionMode)
	{
		ProjectionMode_ = _ProjectionMode;
	}

	inline GameEngineRenderTarget* GetCameraRenderTarget()
	{
		return CameraBufferTarget_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	ProjectionMode ProjectionMode_;
	float FovAngleY_;
	float4 CamSize_;
	float NearZ_;
	float FarZ_;

	void ClearCameraTarget();

	void Render();
	void DebugRender();

	void ReleaseRenderer();

	void CameraTransformUpdate();

	std::map<int, std::list<GameEngineRenderer*>> RendererList_;
	// std::set<int> ZSort_;

	int DebugRenderCount_;
	std::vector<GameEngineDebugRenderData> DebugVector_;

};

