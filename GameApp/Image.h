#pragma once
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineActor.h>

class GameEngineImageRenderer;

class Image : public GameEngineActor
{
public:
	Image(); 
	~Image(); 

private:		
	Image(const Image& _other) = delete;
	Image(Image&& _other) = delete;
	Image& operator=(const Image& _other) = delete; 
	Image& operator=(const Image&& _other) = delete; 

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	GameEngineImageRenderer* ImageRenderer_;

private:
	float LifeTime_;
	float TimeCheck_;
	std::function<void()> DeathFuction_;
public:
	GameEngineImageRenderer*  CreateImageRenderer(float4 _Scale, float4 _Pos);

	void ImageSetImage(const std::string& _TextureName);
	void ImageCreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop);
	void ImageCreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop = true);

	void SetReserveDeath(std::string _Name);

	void SetAnimationFrame(int Frame);

	void SetImageDeathFuction(std::function<void()> _CallBack);
	void SetImageDeathTime(float _LifeTime);
	void EffectDeath();
};

