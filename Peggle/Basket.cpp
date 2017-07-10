#include "stdafx.h"
#include "Basket.h"

Basket::Basket()
	: center(.0f, .0f, .0f)
	, basketPosition(0, 330, 0)
	, dirX(1), dirY(0)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"Images/Basket.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &basketTexture));

	center = D3DXVECTOR3(info.Width / 2, info.Height / 2, 0.f);
}


Basket::~Basket()
{
	ReleaseCOM(basketTexture);
}

void Basket::Update()
{
	basketPosition += D3DXVECTOR3(dirX,dirY, 0) * basketSpeed * gD3DApp->GetTimer()->GetDeltaTime();
	
	//std::cout << basketPosition.x << std::endl;


	if (basketPosition.x <= rightBorder)
	{
		basketSpeed *= -1;
	}

	if (basketPosition.x >= leftBorder)
	{
		basketSpeed *= -1;
	}
}

void Basket::Draw(ID3DXSprite * spriteBatch)
{
	HR(spriteBatch->Draw(basketTexture, 0, &center, &basketPosition, D3DCOLOR_XRGB(255, 255, 255)));
	HR(spriteBatch->Flush());
}
