#include "flib.h"
#include "flib_vec2.h"
#include "SC_Sprite-texture-image.h"

TGfxSprite * SC_CreateSprite(TSprite & tSprite, const int iTileX, const int iTileY, const float fTileSize, const float fSize)
{
	tSprite.pTexture = Create_Texture(tSprite);
	tSprite.pSprite = GfxSpriteCreate(tSprite.pTexture);
	GfxSpriteSetCutout(tSprite.pSprite, iTileX, iTileY, fTileSize, fTileSize);
	GfxSpriteSetFilteringEnabled(tSprite.pSprite, false);
	GfxSpriteSetScale(tSprite.pSprite, fSize, fSize);
	GfxSpriteSetPosition(tSprite.pSprite, tSprite.tPosition.x, tSprite.tPosition.y);

	return tSprite.pSprite;
}

