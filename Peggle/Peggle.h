#include "stdafx.h"

#include "d3dApp.h"

#include "Background.h"
#include "Basket.h"
#include "Balle.h"
#include "Canon.h"

class Peggle 
	: public D3DApp
{
public:
	Peggle();
	Peggle(HINSTANCE hInstance, int nCmdShow);
	~Peggle();

	void Update();
	void Draw();

private:
	ID3DXSprite* spriteBatch;

	// Objets
	Background background;
	Balle balle;
	Basket basket;
	Canon canon;

	// Camera
	D3DXMATRIX view;
	D3DXMATRIX ortho;
	D3DXVECTOR3 eyePos;
	D3DXVECTOR3 target;
	D3DXVECTOR3 up;
};
