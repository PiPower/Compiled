/*float4 main(float2 col : Color ) : SV_Target
{
	col.x = abs(col.x);
    col.y = abs(col.y);
	return float4(col,1.0f,1.0f);
}*/

cbuffer cBuff
{
    float2 translation;
    float scalling;
    int Iteration;
};
float4 main(float2 col : Color) : SV_Target
{
//col.x *= scalling;
//col.y *= scalling;
//col.x += translation.x;
//col.y += translation.y;

int iteration = 0;
float ax = 0;
float ay = 0;
while (ax * ax + ay * ay <= 4 && iteration < 220)
{
    float delta_X = ax * ax - ay * ay + col.x;
    ay = 2 * ax * ay + col.y;
    ax = delta_X;
    iteration++;
}
return float4(iteration * 2 / 255, iteration * 6 / 255, iteration * 3.2 / 255, 1.0f);
}