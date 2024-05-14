struct VS_IN
{
	float4 position : POSITION0;
	float4 color : COLOR0;
};

struct PS_IN
{
	float4 position : SV_POSITION;
 	float4 color : COLOR;
};

PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;
	
	output.position = input.position;
	output.color = input.color;
	
	return output;
}

float4 PSMain( PS_IN input ) : SV_Target
{
	float4 color = input.color;
#ifdef TEST
	if (input.position.x > 400) color = TCOLOR;
#endif
	return color;
}
