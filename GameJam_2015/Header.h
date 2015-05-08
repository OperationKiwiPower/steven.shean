#ifndef HEADER_LUCIOL
#define HEADER_LUCIOL

const int g_iNumberPlayer = 4;
const int g_iNumberAmmo = 20;
const int g_iNumberEnnemy = 50;

int g_iNumberPlayerInGame = 0;
int g_iCounter = 0;

TGfxVec2 g_tMouvement[g_iNumberPlayer];
TGfxVec2 g_tDirection[g_iNumberPlayer];

enum EStateEvolution
{
	EStateEvol_1 = 1,
	EStateEvol_2,
	EStateEvol_3,
	EStateEvol_4,
	EStateEvol_5,
};
struct TState
{
	EStateEvolution m_tEvolution;
};
struct TSprite
{
	TGfxVec2 tPosition;
	TGfxVec2 tPositionInitial;
	TGfxSprite * pSpriteEvol_1[2];
	TGfxSprite * pSpriteEvol_2[2];
	TGfxSprite * pSpriteEvol_3[2];
	TGfxSprite * pSpriteEvol_4[2];
	TGfxSprite * pSpriteArrow;

	TGfxSprite * pSpriteAmmo[g_iNumberAmmo];
	TGfxVec2 tAmmoPositionInitial[g_iNumberAmmo];
	TGfxVec2 tAmmoDepl[g_iNumberAmmo];
	int iAmmoNow = 0;

	float fSpeed = 3.0f;
	float fRatio = 10;
	int iFrame = 0;
};
struct TEnnemy
{
	TGfxSprite * pSprite;
	TGfxVec2 tPosition;
	bool bActif = false;
};
struct TTexture
{
	TGfxTexture * pTexture_16;
	TGfxTexture * pTexture_32;
	TGfxTexture * pTexture_64;
	TGfxTexture * pTexture_128;
	TGfxTexture * pTexture_Arrow;
	TGfxTexture * pTexture_Ammo;
	TGfxTexture * pTexture_Ennemy;
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

TState g_tEvol[g_iNumberPlayer];
TSprite g_tPlayer[g_iNumberPlayer];
TEnnemy g_tEnnemy[g_iNumberEnnemy];
TTexture g_tTexture;
TDisplay g_tDisplay;
TMousse g_tMousse;
TMousse g_tCOntroller[g_iNumberPlayer];

#endif
