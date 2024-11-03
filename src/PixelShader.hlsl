
Texture2D tex : register(t0);
SamplerState samplerState : register(s0);


struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};
float4 main(VS_OUTPUT input) : SV_TARGET
{
    return tex.Sample(samplerState, float2(input.Color.r, input.Color.g));
}