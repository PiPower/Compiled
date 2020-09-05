cbuffer cBuff
{
    double2 translation;
    double scalling;
    int Iterations;
};
float4 main(float2 complex : Color) : SV_Target
{
 double  x = complex.x;
 double y = complex.y;
 x*= scalling;
 y *= scalling;
 x += translation.x;
 y += translation.y;

int iteration = 0;
double ax = 0;
double ay = 0;
while (ax * ax + ay * ay <= 4 && iteration < Iterations)
{
    double delta_X = ax * ax - ay * ay + x;
    ay = 2 * ax * ay + y;
    ax = delta_X;
    iteration++;
}
return float4(sin(iteration*0.45)* sin(iteration * 0.45), cos(iteration * 0.45)* cos(iteration * 0.45), iteration * 3.2 / 255, 1.0f);
//return float4((float)iteration / Iterations, (float)iteration / Iterations, (float)iteration / Iterations, 1.0f);
}
