Texture2D tex;
SamplerState sam;

float4 main(float4 position : SV_POSITION, float2 texCoord : TEXCOORD0) : SV_TARGET
{
	
	float4 col= tex.Sample(sam,texCoord);
	// if (col.r == 1 && col.g == 1 && col.b == 1) { clip(-1); };
	return col;
}