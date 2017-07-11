#include "stdafx.h"
#include "Canon.h"

Canon::Canon()
	: center(.0f, .0f, .0f)
	, position(0, -310, 0)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"Images/Canon.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &texture));

	center = D3DXVECTOR3(info.Width / 2, info.Height , 0.f);
}


Canon::~Canon()
{
	ReleaseCOM(texture);
}


void Canon::Update()
{
	if (rotEuler.z >= -0.15f)
	{
		if (gD3DApp->GetInput()->KeyDown(DIK_LEFT))
		{
			rotEuler.z -= 1* gD3DApp->GetTimer()->GetDeltaTime();
		}
	}

	if (rotEuler.z <= 0.15f)
	{
		if (gD3DApp->GetInput()->KeyDown(DIK_RIGHT))
		{
			rotEuler.z += 1 * gD3DApp->GetTimer()->GetDeltaTime();
		}
	}
	std::cout << rotEuler.z << std::endl;
}

void Canon::Draw(ID3DXSprite * spriteBatch)
{
	D3DXMATRIX rotMatrix;
	D3DXMatrixIdentity(&rotMatrix);

	// Rotate 90 degree
	D3DXMatrixRotationYawPitchRoll(&rotMatrix, rotEuler.x, rotEuler.y, rotEuler.z);
	HR(spriteBatch->SetTransform(&rotMatrix));

	// Draw the Canon
	D3DXVECTOR3 offset = { 0, 0, 0, };
	HR(spriteBatch->Draw(texture, 0, &center, &(position + offset), D3DCOLOR_XRGB(255, 255, 255)));
	
	// Restore rotation
	D3DXMatrixIdentity(&rotMatrix);
	HR(spriteBatch->SetTransform(&rotMatrix));

	HR(spriteBatch->Flush());
}
