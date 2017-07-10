#pragma once
#include "stdafx.h"
#include "D3DApp.h"
class Canon
{
public:
	Canon();
	~Canon();

	void Update();
	void Draw(ID3DXSprite* spriteBatch);
	D3DXVECTOR3 rotEuler = { 0.0f, 0.0f, D3DX_PI / 4 };

private:
	// Sprite
	IDirect3DTexture9* texture;
	D3DXIMAGE_INFO info;
	D3DXVECTOR3 position;
	D3DXVECTOR3 center;
};

