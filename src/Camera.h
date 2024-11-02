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
    static Camera &getInstance()
    {
        static Camera instance;
        return instance;
    }

    Camera(const Camera &) = delete;
    Camera &operator=(const Camera &) = delete;

    void setCamera(
        DirectX::XMVECTOR camPosition,
        DirectX::XMVECTOR camTarget,
        DirectX::XMVECTOR camUp);
    void setProjection(float fov, float aspectRatio, float nearZ, float farZ);

    DirectX::XMMATRIX getWVP();
};