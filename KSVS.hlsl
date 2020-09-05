struct VSOut
{
    float4 col: Color;
    float4 pos: SV_Position;
};

VSOut main(float2 Pos:Position, float3 col : Color)
{
    VSOut vsout;
    vsout.pos = float4(Pos, 0, 1);
    vsout.col = float4(col, 1);
    return vsout;
}