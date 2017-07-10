#include "stdafx.h"
#include "Balle.h"

Balle::Balle()
	: center(.0f, .0f, .0f)
	, ballPosition(200,0,0)
	, dirX(1), dirY(1)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"Images/Balle.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &balleTexture));

	center = D3DXVECTOR3(info.Width / 2, info.Height / 2, 0.f);

	prevPos = ballPosition;
}

Balle::~Balle()
{
	ReleaseCOM(balleTexture);
}

void Balle::Update()
{
	if (ballPosition.x <= leftBorder || ballPosition.x >= rightBorder)
	{
		ballPosition = prevPos;
		dirX *= -1;		
	}
	
	if (ballPosition.y <= bottomBorder || ballPosition.y >= topBorder)
	{
		ballPosition = prevPos;
		dirY *= -1;
	}
	prevPos = ballPosition;
	ballPosition += D3DXVECTOR3(dirX, dirY, 0) * balleSpeed * gD3DApp->GetTimer()->GetDeltaTime();

	//gD3DApp->GetInput()->KeyDown(DIK_LEFT)
}

void Balle::Draw(ID3DXSprite* spriteBatch)
{
	HR(spriteBatch->Draw(balleTexture, 0, &center, &ballPosition, D3DCOLOR_XRGB(255, 255, 255)));
	HR(spriteBatch->Flush());
}
