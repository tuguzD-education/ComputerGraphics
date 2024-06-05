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
};

VS_Output VSMain(VS_Input input)
{
    VS_Output output = (VS_Output)0;

    output.position = sign(float4(input.position, 1.0f));
    output.texture_coordinate = (output.position.xy + 1.0f) / 2.0f;

    return output;
}

typedef VS_Output PS_Input;

float4 PSMain(PS_Input input) : SV_Target
{
    float size = 2 - (0.00125 * 12);

    float2 total = floor(input.position.xy * size);

    //float mask = fmod(total.x + fmod(total.y, 2.0f), 2.0f);
    //return mask * float4(1.0f, 1.0f, 1.0f, 1.0f);

    bool isEven = fmod(total.x + fmod(total.y, 2.0f), 2.0f) == 0.0f;
    return isEven ? float4(0.6f, 0.3f, 0.0f, 1.0f) : float4(0.8f, 0.8f, 0.8f, 1.0f);
}
