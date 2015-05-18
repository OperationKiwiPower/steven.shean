#include "flib.h"
#include "flib_vec2.h"

struct TSprite
{
	TGfxVec2 tPosition;
	TGfxVec2 tPositionInitial;
	TGfxSprite * pSprite;
};
TSprite g_tPlayer;

void Initialize()
{
g_tPlayer.pSprite = 

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
