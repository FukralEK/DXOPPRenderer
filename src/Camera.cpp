#include "Camera.h"

void Camera::setCamera(DirectX::XMVECTOR camPosition, DirectX::XMVECTOR camTarget, DirectX::XMVECTOR camUp)
{
    camView = DirectX::XMMatrixLookAtLH(camPosition, camTarget, camUp);
}

void Camera::setProjection(float fov, float aspectRatio, float nearZ, float farZ)
{
    camProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspectRatio, 0.01f, 1000.0f);
}

DirectX::XMMATRIX Camera::getWVP()
{
    World = DirectX::XMMatrixIdentity();

    WVP = World * camView * camProjection;

    WVP = DirectX::XMMatrixTranspose(WVP);

    return WVP;
}
