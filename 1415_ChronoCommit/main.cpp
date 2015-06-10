#include "flib.h"

struct TTime
{
	TGfxSprite * pTextSprite;
	int iFirst;
	int iNow;
	int iBetween;
	int iRestTime;
};
TTime g_tTime;
const int iMaxTimeBetween = 3600000;// 1 heure;

int SC_GetTime()
{
	int iTime;
	
	g_tTime.iNow = GfxTimeGetMilliseconds();
	g_tTime.iBetween = g_tTime.iNow - g_tTime.iFirst;
	iTime = iMaxTimeBetween - g_tTime.iBetween;
	return iTime;
}

void Initialize()
{
	g_tTime.iFirst = GfxTimeGetMilliseconds();
	g_tTime.pTextSprite = GfxTextSpriteCreate();

}
void Update()
{
	g_tTime.iRestTime = SC_GetTime();

	GfxTextSpritePrintf(g_tTime.pTextSprite, "Il reste : ", g_tTime.iRestTime);

}
void Render()
{

}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
