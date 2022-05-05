#include "PreCompile.h"
#include "GameEngineImageRenderer.h"

void GameEngineImageRenderer::Animation2D::CallEnd()
{
	for (auto& CallBack : EndCallBack_)
	{
		CallBack();
	}
}
void GameEngineImageRenderer::Animation2D::CallFrame()
{
	for (auto& CallBack : FrameCallBack_)
	{
		if (CallBack.first != CurFrame_)
		{
			continue;
		}

		if (CallBack.second.size() == 0)
		{
			continue;
		}

		for (size_t i = 0; i < CallBack.second.size(); i++)
		{
			CallBack.second[i]();
		}
	}
}

void GameEngineImageRenderer::Animation2D::Reset()
{
	IsEnd = false;
	CurTime_ = InterTime_;
	CurFrame_ = StartFrame_;
}

void GameEngineImageRenderer::Animation2D::FrameUpdate()
{
	if (CurTime_ <= 0.0f)
	{
		CallFrame();
		++CurFrame_;

		CurTime_ = InterTime_;

		if (true == Loop_ && CurFrame_ > EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}

		else if (false == Loop_ && CurFrame_ > EndFrame_)
		{
			if (false == IsEnd)
			{
				CallEnd();
			}

			IsEnd = true;

			CurFrame_ = EndFrame_;
		}
	}

}

void GameEngineImageRenderer::Animation2D::ReverseFrameUpdate()
{
	if (CurTime_ <= 0.0f)
	{
		CallFrame();
		--CurFrame_;

		CurTime_ = InterTime_;

		if (true == Loop_ && CurFrame_ < EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}

		else if (false == Loop_ && CurFrame_ < EndFrame_)
		{
			if (false == IsEnd)
			{
				CallEnd();
			}

			IsEnd = true;

			CurFrame_ = EndFrame_;
		}
	}

}

void GameEngineImageRenderer::Animation2D::Update(float _DeltaTime)
{

	if (true == Renderer->IsPlay_)
	{
		CurTime_ -= _DeltaTime;
	}

	if (StartFrame_ < EndFrame_)
	{
		FrameUpdate();
	}
	else
	{
		ReverseFrameUpdate();
	}

	//CallFrame();
	if (nullptr == FolderTextures_)
	{
		Renderer->ShaderHelper.SettingTexture("Tex", AnimationTexture_);
		Renderer->CurTexture = AnimationTexture_;
		Renderer->SetIndex(CurFrame_);
	}
	else
	{
		Renderer->CutData = float4(0, 0, 1, 1);
		Renderer->ShaderHelper.SettingTexture("Tex", FolderTextures_->GetTextureIndex(CurFrame_));
	}
}
