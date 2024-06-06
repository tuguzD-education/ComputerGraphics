#include "transform.hlsl"

cbuffer ConstantBuffer : register(b0)
{
    Transform transform;
    float4x4 directional_light_shadow_map_view_projection;
    float2 tile_count;
    float2 _unused;
    float time;
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
    float3 normal : NORMAL0;
    float4 color : COLOR0;
    float2 texture_coordinate : TEXCOORD0;
    float3 world_position : TEXCOORD1;
    float4 directional_light_shadow_map_position : TEXCOORD2;
};

VS_Output VSMain(VS_Input input)
{
    VS_Output output = (VS_Output)0;

    input.texture_coordinate.x += time * 0.1f;
    input.texture_coordinate.y += time * 0.1f;

    output.position = mul(WorldViewProjection(transform), float4(input.position, 1.0f));
    output.normal = normalize(mul(transform.world, float4(input.normal, 0.0f)).xyz);
    output.color = input.color;
    output.texture_coordinate = input.texture_coordinate * tile_count;
    output.world_position = mul(transform.world, float4(input.position, 1.0f)).xyz;
    output.directional_light_shadow_map_position = mul(
        directional_light_shadow_map_view_projection, float4(output.world_position.xyz, 1.0f)
    );

    return output;
}
