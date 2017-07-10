#pragma once
#include "stdafx.h"
#include "D3DApp.h"
class Basket
{
public:
	Basket();
	~Basket();

	void Update();
	void Draw(ID3DXSprite* spriteBatch);
	D3DXVECTOR3 basketPosition;
private:
	// Sprite
	IDirect3DTexture9* basketTexture;
	D3DXIMAGE_INFO info;
	D3DXVECTOR3 center;

	float basketSpeed = 200;
	int dirX, dirY;

	int rightBorder = 590;
	int leftBorder = -600;
};


