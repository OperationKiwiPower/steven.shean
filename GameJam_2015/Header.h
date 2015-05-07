#ifndef HEADER_LUCIOL
#define HEADER_LUCIOL

TGfxVec2 g_tMouvement;
TGfxVec2 g_tDirection;


const int g_iNumberPlayer = 4;

int g_iNumberPlayerInGame = 0;

struct TSprite
{
	TGfxVec2 tPosition;
	TGfxVec2 tPositionInitial;
	TGfxSprite * pSprite;
	float fSpeed = 5;
	float fRatio = 10;

};
struct TDisplay
{
	struct TSize
	{
		int iFull;
		int iHalf;
		int iQuart;
		int iTriQuart;
	};
	TSize X;
	TSize Y;
};
struct TMousse
{
	TGfxVec2 tMousse;
};
TSprite g_tPlayer[g_iNumberPlayer];
TDisplay g_tDisplay;
TMousse g_tMousse;
TMousse g_tCOntroller[g_iNumberPlayer];

#endif // !1
