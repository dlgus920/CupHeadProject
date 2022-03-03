#include "CbufferHeader.fx"

struct VertexIn
{
    float4 Position : POSITION;
    float4 Texcoord : TEXTURECOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float4 Texcoord : TEXTURECOORD;
};

cbuffer TextureCutData : register(b1)
{
    // 0.0f 0.0f 
    float2 TextureCutDataPos;
    // 1 / 8 1 / 8
    float2 TextureCutDataSize;
};


VertexOut Texture_VS(VertexIn _in)
{
    VertexOut Out;

    Out.Position = _in.Position;

    Out.Position.w = 1.0f;
    Out.Position = mul(Out.Position, WVP);

    Out.Texcoord = _in.Texcoord;

    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 Texture_PS(VertexOut _in) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _in.Texcoord.xy);
    return Color;
}


