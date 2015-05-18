#include "flib.h"
#include "flib_vec2.h"
#include "SC_Sprite-texture-image.h"

TGfxSprite * SC_CreateSprite(TSprite & tSprite)
{
	tSprite.pSprite = GfxSpriteCreate(tSprite.pTexture);


	return tSprite.pSprite;
}

