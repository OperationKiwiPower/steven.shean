#include "flib.h"
#include "flib_vec2.h"
#include "SC_Sprite-texture-image.h"

const int g_iNumberEnnemy = 50;


TSprite g_tPlayer;
TSprite g_tEnnemi[g_iNumberEnnemy];

void Initialize()
{
	g_tPlayer.pSprite = SC_CreateSprite(g_tPlayer,12,12,16,3);
	for (int i = 0; i < g_iNumberEnnemy; i++)
	{
		g_tEnnemi[i].pSprite = SC_CreateSprite(g_tEnnemi[i],5, 5, 16, 3);
	}
}
void Update()
{

}
void Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_tPlayer.pSprite);
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
