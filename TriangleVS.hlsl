struct VSOut
{
    float4 col: Color;
    float4 pos: SV_Position;
};

cbuffer cBuff
{
    double2 translation;
    double scalling;
};

VSOut main(float2 Pos:Position, float3 col : Color)
{
    VSOut vsout;
    vsout.pos = float4(Pos, 0, 1);
    vsout.col = float4(col, 1);

    vsout.pos.x += translation.x;
    vsout.pos.y += translation.y;

    vsout.pos.x *= scalling;
    vsout.pos.y *= scalling;

    return vsout;
}