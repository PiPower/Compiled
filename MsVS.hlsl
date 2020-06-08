struct VSOut
{
	float2 complex: Color;
    float4 pos: SV_Position;
};

VSOut main(float2 Pos:Position, float2 complex : Color)
{
    VSOut vsout;
    vsout.pos = float4(Pos, 0, 1);
    vsout.complex = complex;
    return vsout;
}
