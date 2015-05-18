#include "flib.h"
#include "flib_vec2.h"
#include "SC_Sprite-texture-image.h"

TSprite g_tPlayer;
TSprite g_tEnnemi[50];

void Initialize()
{
	g_tPlayer.pSprite = SC_CreateSprite(g_tPlayer);

	g_tEnnemi[1].pSprite = SC_CreateSprite(g_tEnnemi[1]);

}
void Update()
{

}
void Render()
{

}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
