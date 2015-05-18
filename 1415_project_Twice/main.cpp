#include "flib.h"
#include "flib_vec2.h"
#include "SC_Sprite-texture-image.h"

const int g_iNumberEnnemy = 50;


TSprite g_tPlayer;
TSprite g_tEnnemi[g_iNumberEnnemy];

void Initialize()
{
	g_tPlayer.pSprite = SC_CreateSprite(g_tPlayer);
	for (int i = 0; i < g_iNumberEnnemy; i++)
	{
		g_tEnnemi[1].pSprite = SC_CreateSprite(g_tEnnemi[i]);
	}
}
void Update()
{

}
void Render()
{
	GfxClear(EGfxColor_Black);

}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
