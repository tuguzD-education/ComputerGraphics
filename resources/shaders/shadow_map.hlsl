#include "transform.hlsl"

cbuffer VSConstantBuffer : register(b0)
{
    Transform transform;
}

struct VS_Input
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float4 color : COLOR0;
    float2 texture_coordinate : TEXCOORD0;
};

struct VS_Output
{
    float4 position : SV_Position0;
};

VS_Output VSMain(VS_Input input)
{
    VS_Output output = (VS_Output)0;

    output.position = mul(WorldViewProjection(transform), float4(input.position, 1.0f));

    return output;
}

typedef VS_Output PS_Input;

float4 PSMain(PS_Input input) : SV_Target
{
    float depth = input.position.z / input.position.w;
    float4 color = float4(depth, depth, depth, 1.0f);
    return color;
}
