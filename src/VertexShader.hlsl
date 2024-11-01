cbuffer cbPerObject
{
    matrix wvpMatrix;
    float4 position;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VS_OUTPUT main(float4 inPos : POSITION, float4 inColor : COLOR)
{
    VS_OUTPUT output;

    float4 finalPos = inPos + position;

    output.Pos = mul(finalPos, wvpMatrix);

    output.Color = inColor;

    return output;
}