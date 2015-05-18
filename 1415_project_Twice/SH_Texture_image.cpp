#include "flib.h"
#include "flib_vec2.h"
#include "SC_Sprite-texture-image.h"

TGfxTexture * Create_Texture(TSprite & tSprite)
{
	TGfxImage * pImage = GfxImageLoad("tileset.tga");
	tSprite.pTexture = GfxTextureCreate(pImage);
	return tSprite.pTexture;
}
