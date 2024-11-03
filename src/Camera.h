#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

class Camera
{
private:
    Camera()
    {
    }

    DirectX::XMMATRIX WVP;
    DirectX::XMMATRIX World;
    DirectX::XMMATRIX camView;
    DirectX::XMMATRIX camProjection;

    float fov;
    float aspectRatio;
    float nearZ;
    float farZ;

public:
    int faces = 0;
    int drawCalls = 0;

    static Camera &getInstance()
    {
        static Camera instance;
        return instance;
    }
    float color[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    Camera(const Camera &) = delete;
    Camera &operator=(const Camera &) = delete;

    void setCamera(
        DirectX::XMVECTOR camPosition,
        DirectX::XMVECTOR camTarget,
        DirectX::XMVECTOR camUp);
    void setProjection(float fov, float aspectRatio, float nearZ, float farZ);

    DirectX::XMMATRIX getWVP();
};