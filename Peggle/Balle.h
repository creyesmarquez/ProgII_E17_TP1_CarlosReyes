#pragma once
#include "stdafx.h"
#include "D3DApp.h"
class Balle 
{
public:
	Balle();
	~Balle();

	void Update();
	void Draw(ID3DXSprite* spriteBatch);

private:
	// Sprite
	IDirect3DTexture9* balleTexture;
	D3DXIMAGE_INFO info;
	D3DXVECTOR3 center;
	D3DXVECTOR3 ballPosition;

	int dirX, dirY;

	D3DXVECTOR3 prevPos;
	float balleSpeed = 200;
	int topBorder = 340;
	int bottomBorder = -340;
	int rightBorder = 590;
	int leftBorder = -630;
};

