cbuffer cbPerObject
{
    float4 Tester;
};


struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VS_OUTPUT main(float4 inPos : POSITION, float4 inColor : COLOR)
{
    VS_OUTPUT output;

    output.Pos = float4(inPos.x * Tester.x, inPos.y *Tester.y, inPos.z * Tester.z, inPos.w);
    output.Color = inColor;

    return output;
}