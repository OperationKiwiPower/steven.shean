#ifndef SC_SPRITE_HEADER
#define SC_SPRITE_HEADER

struct TSprite
{
	TGfxSprite * pSprite;
	TGfxVec2 tPosition;
	TGfxVec2 tPositionInit;
	TGfxTexture * pTexture;
};

TGfxTexture * Create_Texture(TSprite & tSprite);
TGfxSprite * SC_CreateSprite(TSprite & tSprite, const int iTileX, const int iTileY, const float fTileSize, const float fSize);

#endif // !SC_SPRITE_HEADER
