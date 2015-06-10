#include "flib.h"

struct TTime
{
	TGfxSprite * pTextSprite;
	int iFirst;
	int iNow;
	int iBetween;
	int iRestTime;
};
struct TSegmentTime
{
	int iHour;
	int iMinute;
	int iSecond;
};
struct TDisplay
{
	struct TSize
	{
		int full;
		int half;
	};
	TSize X;
	TSize Y;
};

TTime g_tTime;
TSegmentTime g_TSgementTime;
TDisplay g_tDisplay;
unsigned int g_iColor;
int iMaxTimeBetween = 1;// number heure;
TGfxSound * g_pSound;
int g_iCompt = 0;
bool g_bIsOver = false;

int SC_GetTime()
{
	int iTime;	
	g_tTime.iNow = GfxTimeGetMilliseconds();
	g_tTime.iBetween = g_tTime.iNow - g_tTime.iFirst;
	iTime = iMaxTimeBetween - g_tTime.iBetween;
	return iTime;
}
void SC_SegmentTime(const int iTime)
{
	g_TSgementTime.iHour = int(iTime / 3600000.0f);
	if (g_TSgementTime.iHour < 0)g_TSgementTime.iHour = 0;

	g_TSgementTime.iMinute = int((iTime / 60000.0f) - (g_TSgementTime.iHour * 60.0f));
	if (g_TSgementTime.iMinute < 0)g_TSgementTime.iMinute = 0;

	g_TSgementTime.iSecond = int((iTime / 1000.0f) - (g_TSgementTime.iHour * 3600.0f) - (g_TSgementTime.iMinute * 60.0f));
	if (g_TSgementTime.iSecond < 0)g_TSgementTime.iSecond = 0;

	GfxDbgPrintf("time:%i - %ih %im %is\n", iTime, g_TSgementTime.iHour, g_TSgementTime.iMinute, g_TSgementTime.iSecond);
}
void SC_GetDisplaySize()
{
	g_tDisplay.X.full = GfxGetDisplaySizeX();
	g_tDisplay.Y.full = GfxGetDisplaySizeY();
	g_tDisplay.X.half = g_tDisplay.X.full / 2;
	g_tDisplay.Y.half = g_tDisplay.Y.full / 2;
}

void Initialize()
{
	iMaxTimeBetween *= 3600000;// * 1 heure;
	g_tTime.iFirst = GfxTimeGetMilliseconds();
	g_tTime.pTextSprite = GfxTextSpriteCreate();
	GfxSpriteSetFilteringEnabled(g_tTime.pTextSprite, false);
	SC_GetDisplaySize();
	g_iColor = EGfxColor_Black;
	g_pSound = GfxSoundLoad("Alarme.wav");
}
void Update()
{
	g_iCompt++;
	g_tTime.iRestTime = SC_GetTime();
	SC_SegmentTime(g_tTime.iRestTime);
	if (g_tTime.iRestTime <= 0)g_iColor = true;

	GfxTextSpritePrintf(g_tTime.pTextSprite,
				"Il reste: %i h %i m %i s",
				int(g_TSgementTime.iHour), 
				int(g_TSgementTime.iMinute), 
				int(g_TSgementTime.iSecond));
	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		g_iColor = EGfxColor_Black;
		g_tTime.iFirst = GfxTimeGetMilliseconds();
		g_bIsOver = false;
	}
	
	if (g_iCompt % 25 == 0 && g_bIsOver == true)
	{
		GfxSoundPlay(g_pSound);
		if (g_iColor == EGfxColor_Blue)
		{
			g_iColor = EGfxColor_Red;
		}
		else
		{
			g_iColor = EGfxColor_Blue;
		}
	}
	
}
void Render()
{
	GfxClear(g_iColor);

	GfxTextSpriteRender(g_tTime.pTextSprite, float(g_tDisplay.X.half), float (g_tDisplay.Y.half), EGfxColor_White, 2.0f, true, true);
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
