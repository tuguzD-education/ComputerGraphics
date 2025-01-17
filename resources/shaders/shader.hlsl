#include "transform.hlsl"
#include "material.hlsl"
#include "light.hlsl"

cbuffer ConstantBuffer : register(b0)
{
    Transform transform;
    float4x4 directional_light_shadow_map_view_projection;
    float2 tile_count;
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

Texture2D ShadowMapDirectionalLight : register(t0);
SamplerState ShadowMapSampler : register(s0);

Texture2D DiffuseMap : register(t1);
SamplerState TextureSampler : register(s1);

cbuffer PSConstantBuffer : register(b0)
{
    bool has_texture;
    float3 view_position;
    Material material;

    DirectionalLight directional_light;
    PointLight point_light;
}

typedef VS_Output PS_Input;

float4 PhongAmbientLightning(in Light light, in Material material)
{
    return light.ambient * material.ambient;
}

float4 PhongDiffuseLightning(in Light light, in Material material, float3 normal, float3 to_light_direction)
{
    float diffuse = max(dot(to_light_direction, normal), 0.0f);
    return diffuse * light.diffuse * material.diffuse;
}

float4 PhongSpecularLightning(
    in Light light, in Material material, float3 position, float3 normal, float3 to_light_direction)
{
    float3 to_view_direction = normalize(view_position - position);
    float3 reflect_direction = normalize(reflect(to_light_direction, normal));

    float specular = pow(max(dot(-to_view_direction, reflect_direction), 0.0f), material.exponent);
    return specular * light.specular * material.specular;
}

float4 PhongLightning(
    in Light light, in Material material, float3 position, float3 normal, float3 to_light_direction)
{
    float4 ambient = PhongAmbientLightning(light, material);
    float4 diffuse = PhongDiffuseLightning(light, material, normal, to_light_direction);
    float4 specular = PhongSpecularLightning(light, material, position, normal, to_light_direction);
    return ambient + diffuse + specular;
}

float4 DirectionalLightning(
    in DirectionalLight directional_light, in Material material,
    float3 position, float3 normal, float4 directional_light_shadow_map_position)
{
    Light light;
    light.ambient = directional_light.ambient;
    light.diffuse = directional_light.diffuse;
    light.specular = directional_light.specular;

    float4 color = PhongAmbientLightning(light, material);

    float2 shadow_map_texture_coordinate = float2(
        0.5f + (directional_light_shadow_map_position.x / directional_light_shadow_map_position.w * 0.5f),
        0.5f - (directional_light_shadow_map_position.y / directional_light_shadow_map_position.w * 0.5f)
    );
    if ((saturate(shadow_map_texture_coordinate.x) == shadow_map_texture_coordinate.x) &&
        (saturate(shadow_map_texture_coordinate.y) == shadow_map_texture_coordinate.y))
    {
        float shadow_map_depth =
            ShadowMapDirectionalLight.Sample(ShadowMapSampler, shadow_map_texture_coordinate).r;
        float light_depth = directional_light_shadow_map_position.z / directional_light_shadow_map_position.w;

        if (light_depth < shadow_map_depth)
        {
            float3 to_light_direction = -directional_light.direction;

            float4 diffuse = PhongDiffuseLightning(light, material, normal, to_light_direction);
            float4 specular = PhongSpecularLightning(light, material, position, normal, to_light_direction);
            color += diffuse + specular;
        }
    }
    return color;
}

float4 PointLightning(
    in PointLight point_light, in Material material, float3 position, float3 normal)
{
    float3 to_light = point_light.position - position;
    float to_light_distance = length(to_light);
    float4 attenuation =
        point_light.attenuation.const_factor +
        point_light.attenuation.linear_factor * to_light_distance +
        point_light.attenuation.quad_factor * to_light_distance * to_light_distance;
    attenuation = (length(attenuation) > 0.0f) ? attenuation : float4(1.0f, 1.0f, 1.0f, 1.0f);

    Light light;
    light.ambient = point_light.ambient;
    light.diffuse = point_light.diffuse;
    light.specular = point_light.specular;

    float3 to_light_direction = normalize(to_light);

    return PhongLightning(light, material, position, normal, to_light_direction) / attenuation;
}

float4 PSMain(PS_Input input) : SV_Target
{
    float4 color = has_texture
        ? DiffuseMap.Sample(TextureSampler, input.texture_coordinate)
        : float4(1.0f, 1.0f, 1.0f, 1.0f);
    color *= input.color;

    float4 dl_color = DirectionalLightning(
        directional_light, material, input.world_position,
        input.normal, input.directional_light_shadow_map_position);
    float4 pl_color = PointLightning(point_light, material, input.world_position, input.normal);

    float4 l_color = dl_color + pl_color;
    float4 emissive = material.emissive;
    return color * (l_color + emissive);
}
