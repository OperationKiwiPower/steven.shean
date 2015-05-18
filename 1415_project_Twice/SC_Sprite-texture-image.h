#ifndef SC_SPRITE_HEADER
#define SC_SPRITE_HEADER

struct TSprite
{
	TGfxSprite * pSprite;
	TGfxVec2 tPosition;
	TGfxVec2 tPositionInit;
	TGfxTexture * pTexture;
};

TGfxSprite * SC_CreateSprite(TSprite & tSprite);
TGfxTexture * Create_Texture(TSprite & tSprite);

#endif // !SC_SPRITE_HEADER
