#ifndef SC_SPRITE_HEADER
#define SC_SPRITE_HEADER

struct TSprite
{
	TGfxSprite * pSprite;
	TGfxVec2 tPosition;
	TGfxVec2 tPositionInit;
};

TGfxSprite * SC_CreateSprite(const TSprite & tSprite);

#endif // !SC_SPRITE_HEADER
