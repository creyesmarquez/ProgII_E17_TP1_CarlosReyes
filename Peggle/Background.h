#pragma once
#include "stdafx.h"
#include "D3DApp.h"
class Background
{
public:
	Background();
	~Background();

	void Update();
	void Draw(ID3DXSprite* spriteBatch);

private:
	// Sprite
	IDirect3DTexture9* texture;
	D3DXIMAGE_INFO info;
	D3DXVECTOR3 position;
	D3DXVECTOR3 center;
};
