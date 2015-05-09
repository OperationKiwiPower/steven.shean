#ifndef HEADER_LUCIOL
#define HEADER_LUCIOL

const int g_iNumberPlayer = 4;
const int g_iNumberAmmo = 200;
const int g_iNumberEnnemy = 55;
const int g_iNumberGlow = 10;

int g_iWitchChange = 0;
int g_iNumberPlayerInGame = 0;
int g_iNumberEnnemyRender = 0;
int g_iCounter = 0;

bool g_bGodMod = false;
TGfxSprite* g_pTextGod;

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
enum EStateMenu
{
	EStateMenu_principale = 1,
	EStateMenu_tuto,
	EStateMenu_Ingame,
	EStateMenu_4,
	EStateMenu_5,
};

struct TState
{
	EStateEvolution m_tEvolution;
};
struct TMenu
{
	EStateMenu m_tMenu;
};

struct TSprite
{
	TGfxVec2 tPosition;
	TGfxVec2 tPositionInitial;
	TGfxSprite * pSpriteEvol_1[2];
	TGfxSprite * pSpriteEvol_2[2];
	TGfxSprite * pSpriteEvol_3[2];
	TGfxSprite * pSpriteEvol_4[2];
	TGfxSprite * pSpriteEvol_5[2];
	TGfxSprite * pSpriteArrow;
	TGfxSprite * pSpriteScoring;
	TGfxSprite * pSpriteSchield;

	TGfxSprite * pSpriteAmmo[g_iNumberAmmo];
	TGfxVec2 tAmmoPositionInitial[g_iNumberAmmo];
	TGfxVec2 tAmmoDepl[g_iNumberAmmo];

	TGfxSprite * pSpriteBigAmmo;
	TGfxVec2 tBigAmmoPositionInitial;
	TGfxVec2 tBigAmmoDepl;

	int iAmmoNow = 0;
	int iScore = 0;
	float fSpeed = 3.0f;
	float fRatio = 8;
	int iFrame = 0;
	bool bActifSchield = false;
};
struct TEnnemy
{
	TGfxSprite * pSprite[3];
	TGfxVec2 tPosition;
	TGfxVec2 tDepl;
	bool bActif = false;
	float fAngle = 0;

};
struct TTexture
{
	TGfxTexture * pTexture_16;
	TGfxTexture * pTexture_32;
	TGfxTexture * pTexture_64;
	TGfxTexture * pTexture_128;
	TGfxTexture * pTexture_256;
	TGfxTexture * pTexture_Arrow;
	TGfxTexture * pTexture_Ammo;
	TGfxTexture * pTexture_Ennemy;
	TGfxTexture * pTexture_Glow;
	TGfxTexture * pTexture_Shield;
};
struct TText
{
	TGfxSprite * pScore[g_iNumberEnnemy];
	TGfxSprite * pSprite;
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
struct TClock
{
	int fOld;
	int fNew;
	int fBetween;

};
struct TSound
{
	TGfxSound * m_Shoot;
	TGfxSound * m_BigShoot;
	TGfxSound * m_Schield;
	TGfxSound * m_Evol;
};

TState g_tEvol[g_iNumberPlayer];
TMenu g_tMenu;
TSprite g_tPlayer[g_iNumberPlayer];
TEnnemy g_tEnnemy[g_iNumberEnnemy];
TEnnemy g_tGlow[g_iNumberGlow];
TTexture g_tTexture;
TText g_tText;
TDisplay g_tDisplay;
TMousse g_tMousse;
TMousse g_tCOntroller[g_iNumberPlayer];
TClock g_tClock;
TSound g_tSound;

#endif
