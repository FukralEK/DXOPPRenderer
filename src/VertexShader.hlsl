cbuffer cbPerObject
{
    matrix wvpMatrix;
    float4 position;
    float4 rotation;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

float4x4 CreateRotationMatrix(float4 rotation)
{
    float cX = cos(rotation.x);
    float sX = sin(rotation.x);
    float cY = cos(rotation.y);
    float sY = sin(rotation.y);
    float cZ = cos(rotation.z);
    float sZ = sin(rotation.z);

    float4x4 rotationX = float4x4(1, 0, 0, 0,
                                   0, cX, -sX, 0,
                                   0, sX, cX, 0,
                                   0, 0, 0, 1);
                                   
    float4x4 rotationY = float4x4(cY, 0, sY, 0,
                                   0, 1, 0, 0,
                                   -sY, 0, cY, 0,
                                   0, 0, 0, 1);

    float4x4 rotationZ = float4x4(cZ, -sZ, 0, 0,
                                   sZ, cZ, 0, 0,
                                   0, 0, 1, 0,
                                   0, 0, 0, 1);

    // Combine rotations: rotationZ * rotationY * rotationX
    return mul(mul(rotationZ, rotationY), rotationX);
}

VS_OUTPUT main(float4 inPos : POSITION, float4 inColor : COLOR)
{
    VS_OUTPUT output;

    float4 finalPos = inPos;

    finalPos = mul(finalPos, CreateRotationMatrix(rotation));

    finalPos += position;

    output.Pos = mul(finalPos, wvpMatrix);

    output.Color = inColor;

    return output;
}