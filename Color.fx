#include "CbufferHeader.fx"
// b32 ���� �����ߴ��ɷ� �ƴµ�
// �׳� �������� ���ô�.
// 512����Ʈ �� �ִ��ϰ̴ϴ�.

float4 Color_VS(float4 pos : POSITION) : SV_POSITION
{
    // pos *= World;

    pos.w = 1.0f;

    pos = mul(pos, WVP);

    return pos;
}

cbuffer ResultColor : register(b0)
{
    float4 vColor;
};

float4 Color_PS(float4 pos : SV_POSITION) : SV_Target0
{
    return vColor;
}