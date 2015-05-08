#include "flib.h"
#include "flib_vec2.h"
#include <math.h>

TGfxTexture * CreateTexture(const char *pFile)
{
	TGfxImage * pImage = GfxImageLoad(pFile);
	TGfxTexture * pTexture;
	pTexture = GfxTextureCreate(pImage);
	
	return pTexture;
}

TGfxSprite * DrawLine(TGfxSprite * pSprite, TGfxVec2 tPosition, TGfxVec2 tDirection, const float fRatio)
{
	GfxLineSpriteReset(pSprite);
	GfxLineSpriteSetDrawingColor(pSprite, EGfxColor_White);

	GfxLineSpriteJumpTo(pSprite, tPosition.x + cos(GfxMathDegToRad(float(0))) * fRatio, tPosition.y + sin(GfxMathDegToRad(float(0))) * fRatio);
	for (int i = 0; i < 36; i++)
	{
		float fPosX = (cos(GfxMathDegToRad(float(i * 10)))) * fRatio;
		float fPosY = (sin(GfxMathDegToRad(float(i * 10)))) * fRatio;
		fPosX += tPosition.x;
		fPosY += tPosition.y; 
		GfxLineSpriteLineTo(pSprite, fPosX, fPosY);
	}
	float fMore = 3;
	GfxLineSpriteJumpTo(pSprite, tPosition.x + (tDirection.x * fMore) + cos(GfxMathDegToRad(float(0))) * (fRatio / 3), tPosition.y + (tDirection.y * fMore) + sin(GfxMathDegToRad(float(0))) * (fRatio / 3));
	for (int i = 0; i < 36; i++)
	{
		float fPosX = (cos(GfxMathDegToRad(float(i * 10)))) * (fRatio / 3);
		float fPosY = (sin(GfxMathDegToRad(float(i * 10)))) * (fRatio / 3);
		fPosX += tPosition.x + (tDirection.x * fMore);
		fPosY += tPosition.y + (tDirection.y * fMore);
		GfxLineSpriteLineTo(pSprite, fPosX, fPosY);
	}

	return pSprite;
}

TGfxSprite * CreateFairy(TGfxTexture * pTexture, TGfxVec2 tPosition,const int iTileX,const int iTileY,const int iPixelSize, const float fRatio)
{
	TGfxSprite * pSprite = GfxSpriteCreate(pTexture);
	GfxSpriteSetCutout(pSprite, iTileX, iTileY, iPixelSize, iPixelSize);
	GfxSpriteSetFilteringEnabled(pSprite, false);
	GfxSpriteSetScale(pSprite, fRatio, fRatio);
	GfxSpriteSetPivot(pSprite, float(iPixelSize / 2), float(iPixelSize / 2));
	GfxSpriteSetPosition(pSprite, tPosition.x, tPosition.y);

	return pSprite;
}

TGfxSprite * CreateArrow(TGfxTexture * pTexture, TGfxVec2 tPosition, const float fDecal, const int iTileY, const float fRatio)
{
	TGfxSprite * pSprite = GfxSpriteCreate(pTexture);
	GfxSpriteSetFilteringEnabled(pSprite, false);
	GfxSpriteSetCutout(pSprite, 0, iTileY, 16, 16);
	GfxSpriteSetScale(pSprite, fRatio, fRatio);
	GfxSpriteSetPivot(pSprite, -fDecal, 8);
	GfxSpriteSetPosition(pSprite, tPosition.x, tPosition.y);

	return pSprite;
}

TGfxSprite * CreateAmmo(TGfxTexture * pTexture, TGfxVec2 tPosition, const int iTileY, const float fRatio)
{
	TGfxSprite * pSprite = GfxSpriteCreate(pTexture);
	GfxSpriteSetFilteringEnabled(pSprite, false);
	GfxSpriteSetCutout(pSprite, 0, iTileY, 8, 8);
	GfxSpriteSetScale(pSprite, fRatio, fRatio);
	GfxSpriteSetPivot(pSprite, 4, 4);
	GfxSpriteSetPosition(pSprite, tPosition.x, tPosition.y);

	return pSprite;
}

int CheckPad()
{
	int iCounterPad = 0;
	for (int i = 0; i < 4; i++)
	{
		bool bTrue = GfxInputIsPadConnected(i);
		if (bTrue == true)
		{
			iCounterPad++;
		}
		else
		{
			break;
		}
	}
	return iCounterPad;
}

