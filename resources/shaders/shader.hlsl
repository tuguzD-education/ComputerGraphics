#include "transform.hlsl"

cbuffer ConstantBuffer : register(b0)
{
    Transform transform;
    float2 tile_count;
}

struct VS_Input
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
};

struct VS_Output
{
    float4 position : SV_Position;
    float3 normal : NORMAL;
    float4 color : COLOR;
};

VS_Output VSMain(VS_Input input)
{
    VS_Output output = (VS_Output)0;
	
    output.position = mul(WorldViewProjection(transform), float4(input.position, 1.0f));
    output.normal = normalize(mul(transform.world, float4(input.normal, 0.0f)).xyz);
    output.color = input.color;
	
	return output;
}

typedef VS_Output PS_Input;

float4 PSMain(PS_Input input) : SV_Target
{
	float4 color = input.color;

#ifdef TEST
    if (input.position.x > 400) color = TCOLOR;
#endif

	return color;
}
