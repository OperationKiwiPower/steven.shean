#ifndef HEADER_NOTVOID
#define HEADER_NOTVOID

TGfxTexture * CreateTexture(const char *pFile);
TGfxSprite * DrawLine(TGfxSprite * pSprite, TGfxVec2 tPosition, TGfxVec2 tDirection, const float fRatio);
TGfxSprite * CreateAmmo(TGfxTexture * pTexture, TGfxVec2 tPosition, const int iTileY, const float fRatio);
TGfxSprite * CreateArrow(TGfxTexture * pTexture, TGfxVec2 tPosition, const float fDecal, const int iTileY, const float fRatio);
TGfxSprite * CreateFairy(TGfxTexture * pTexture, TGfxVec2 tPosition, const int iTileX, const int iTileY, const int iPixelSize, const float fRatio);

int CheckPad();

#endif 
