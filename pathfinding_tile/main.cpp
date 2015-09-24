#include "flib.h"

const int g_iMaxWall = 400;

TGfxSprite * g_pSpriteMap;
TGfxSprite * g_pSpriteWall[g_iMaxWall];
TGfxTexture * g_pTextureWall;

int g_iMapSizeX;
int g_iMapSizeY;


void PixelDetection(TGfxImage * pImageMap)
{
	for (int y = 0; y < g_iMapSizeY; y++)
	{
		for (int x = 0; x < g_iMapSizeX; x++)
		{

			int iIndex = x + (y * g_iMapSizeX);
			if (GfxImageGetData(pImageMap)[iIndex] == EGfxColor_Red)
			{
				g_pSpriteWall[iIndex] = GfxSpriteCreate(g_pTextureWall);
				GfxSpriteSetPosition(g_pSpriteWall[iIndex], 20.0f*x, 20.0f*y);
			}
		}
	}
}

void Initialize()
{
	TGfxImage * pImageMap;

	pImageMap = GfxImageLoad("pathfinding.tga");
	g_iMapSizeX = GfxImageGetSizeX(pImageMap);
	g_iMapSizeY = GfxImageGetSizeY(pImageMap);

	TGfxTexture * pTexture;
	TGfxImage * pImageWall = GfxImageCreate(g_iMapSizeX, g_iMapSizeY);
	for (int i = 0; i < g_iMapSizeX*g_iMapSizeY; i++)
	{
		GfxImageGetData(pImageWall)[i] = EGfxColor_Blue;
	}
	g_pTextureWall = GfxTextureCreate(pImageWall);
	PixelDetection(pImageMap);

	pTexture = GfxTextureCreate(pImageMap);
	g_pSpriteMap = GfxSpriteCreate(pTexture);
	GfxSpriteSetFilteringEnabled(g_pSpriteMap, false);
	GfxSpriteSetScale(g_pSpriteMap, 20.0f, 20.0f);
}

void Update()
{

}

void Render()
{
	GfxClear(EGfxColor_Black);

	GfxSpriteRender(g_pSpriteMap);
	for (int i = 0; i < g_iMaxWall; i++)
	{
		if (g_pSpriteWall[i] != nullptr)
		{
			GfxSpriteRender(g_pSpriteWall[i]);
		}
	}
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
	GfxDefaultResolution(400, 400);
}
