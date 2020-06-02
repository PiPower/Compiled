struct VSOut
{
	float2 col: Color;
    float4 pos: SV_Position;
};

VSOut main(float2 Pos:Position, float2 col : Color)
{
    VSOut vsout;
    vsout.pos = float4(Pos, 0, 1);
    vsout.col = col;
    return vsout;
}
