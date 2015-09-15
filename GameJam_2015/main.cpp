#include "flib.h"
#include "flib_vec2.h"
#include <math.h>
#include "Header.h"
#include "NotVoid.h"

bool checkAllDead()
{
	for (int i = 0; i < g_iNumberEnnemy; i++)
	{
		if (g_tEnnemy[i].pSprite[0] != nullptr)
		{
			return true;
		}
	}

	return false;
}
bool checkAllPlayerWin()
{
	for (int i = 0; i < g_iNumberPlayerInGame; i++)
	{
		if (g_tEvol[i].m_tEvolution != EStateEvol_5)
		{
			return false;
		}
	}
	return true;
}

void clock()
{
	g_tClock.fNew = GfxTimeGetMilliseconds();
	g_tClock.fBetween = g_tClock.fNew - g_tClock.fOld;
}
void createSprite()
{
	g_tTexture.pTexture_16 = CreateTexture("fairy_16.tga");
	g_tTexture.pTexture_32 = CreateTexture("fairy_32.tga");
	g_tTexture.pTexture_64 = CreateTexture("fairy_64.tga");
	g_tTexture.pTexture_128 = CreateTexture("fairy_128.tga");
	g_tTexture.pTexture_256 = CreateTexture("fairy_256.tga");
	g_tTexture.pTexture_Arrow = CreateTexture("arrow.tga");
	g_tTexture.pTexture_Ammo = CreateTexture("ammo.tga");
	g_tTexture.pTexture_Ennemy = CreateTexture("point.tga");
	g_tTexture.pTexture_Glow = CreateTexture("glow.tga");
	g_tTexture.pTexture_Shield = CreateTexture("shield.tga");
	g_tTexture.pTexture_Text = CreateTexture("text_menu.tga");
	g_tTexture.pTexture_TItle= CreateTexture("title.tga");
	g_tTexture.pTexture_TextGlow = CreateTexture("text_menu.tga");
	g_tTexture.pTexture_BackG = CreateTexture("background_menu.tga");

	g_tTexture.pTexture_Tuto[0] = CreateTexture("tuto1.tga");
	g_tTexture.pTexture_Tuto[1] = CreateTexture("tuto2.tga");
	g_tTexture.pTexture_Tuto[2] = CreateTexture("tuto3.tga");
	g_tTexture.pTexture_Tuto[3] = CreateTexture("tuto4.tga");
	g_tTexture.pTexture_Tuto[4] = CreateTexture("tuto5.tga");

	g_tMenuSprite[0].pSpritePlay = CreateText(g_tTexture.pTexture_Text, TGfxVec2(0, 0), 0, 0, 128, 1);
	g_tMenuSprite[0].pSpriteExit = CreateText(g_tTexture.pTexture_Text, TGfxVec2(0, 0), 0, 128, 128, 1);
	g_tMenuSprite[0].pSpriteTutoriel = CreateText(g_tTexture.pTexture_Text, TGfxVec2(0, 0), 0, 256, 128, 1);
	g_tMenuSprite[0].pSpriteTitle = CreateText(g_tTexture.pTexture_TItle, TGfxVec2(0, 0), 0, 0, 1024, 0.5f);
	g_tMenuSprite[1].pSpritePlay = CreateText(g_tTexture.pTexture_Text, TGfxVec2(0, 0), 256, 0, 128, 1);
	g_tMenuSprite[1].pSpriteExit = CreateText(g_tTexture.pTexture_Text, TGfxVec2(0, 0), 256, 128, 128, 1);
	g_tMenuSprite[1].pSpriteTutoriel = CreateText(g_tTexture.pTexture_Text, TGfxVec2(0, 0), 256, 256, 128, 1);
//	g_tMenuSprite[1].pSpriteTitle = CreateText(g_tTexture.pTexture_Text, TGfxVec2(0, 0), 256, 384, 128, 1);

	g_tMenuSprite[0].pSpriteBackground = CreateBackground(g_tTexture.pTexture_BackG, 1600, 900, 2);

	for (int i = 0; i < 2; i++)
	{
		GfxSpriteSetPosition(g_tMenuSprite[0].pSpriteBackground, 0, 0);
		GfxSpriteSetPosition(g_tMenuSprite[i].pSpritePlay, float(g_tDisplay.X.iQuart) / 2, float(g_tDisplay.Y.iQuart));
		GfxSpriteSetPosition(g_tMenuSprite[i].pSpriteExit, float(g_tDisplay.X.iQuart) / 2, float(g_tDisplay.Y.iHalf));
		GfxSpriteSetPosition(g_tMenuSprite[i].pSpriteTutoriel, float(g_tDisplay.X.iQuart) / 2, float(g_tDisplay.Y.iTriQuart));
		GfxSpriteSetPosition(g_tMenuSprite[0].pSpriteTitle, float(g_tDisplay.X.iTriQuart), float(g_tDisplay.Y.iHalf)-64);
		GfxSpriteSetFilteringEnabled(g_tMenuSprite[0].pSpriteTitle, true);
	}
	for (int i = 0; i < g_iNumberTutotPage; i++)
	{
		g_tTuto[i].pSprite = CreateBackground(g_tTexture.pTexture_Tuto[i],1280,1024,1);
		GfxSpriteSetScale(g_tTuto[i].pSprite, (float(g_tDisplay.Y.iFull) / GfxSpriteGetSizeY(g_tTuto[i].pSprite)), (float(g_tDisplay.Y.iFull) / GfxSpriteGetSizeY(g_tTuto[i].pSprite)));
		GfxSpriteSetPivot(g_tTuto[i].pSprite, float(GfxSpriteGetSizeX(g_tTuto[i].pSprite) / 2), float(GfxSpriteGetSizeY(g_tTuto[i].pSprite) / 2));
		GfxSpriteSetPosition(g_tTuto[i].pSprite, float(g_tDisplay.X.iHalf), float(g_tDisplay.Y.iHalf));
	}
	for (int i = 0; i < g_iNumberGlow; ++i)
	{
		g_tGlow[i].pSprite[0] = CreateFairy(g_tTexture.pTexture_Glow, g_tGlow[i].tPosition, 0, 0, 256, 2);
		g_tGlow[i].tPosition.x = float(GfxMathGetRandomInteger(0, g_tDisplay.X.iFull));
		g_tGlow[i].tPosition.y = float(GfxMathGetRandomInteger(0, g_tDisplay.Y.iFull));
		g_tGlow[i].fAngle = float(GfxMathGetRandomFloat(0, 360));
		GfxSpriteSetColor(g_tGlow[i].pSprite[0], GfxColor(150, 255, 150, 50));
	}
	for (int i = 0; i < g_iNumberEnnemy; ++i)
	{
		g_tEnnemy[i].pSprite[0] = CreateFairy(g_tTexture.pTexture_Ennemy, g_tEnnemy[i].tPosition, 0, 0, 32, 1);
		g_tEnnemy[i].pSprite[1] = CreateFairy(g_tTexture.pTexture_Ennemy, g_tEnnemy[i].tPosition, 32, 0, 32, 1);
		g_tEnnemy[i].pSprite[2] = CreateFairy(g_tTexture.pTexture_Ennemy, g_tEnnemy[i].tPosition, 0, 0, 32, 1);
		g_tEnnemy[i].tPosition = TGfxVec2(float(GfxMathGetRandomInteger(16, g_tDisplay.X.iFull - 16)), float(GfxMathGetRandomInteger(16, g_tDisplay.Y.iFull - 16)));
		GfxSpriteSetPosition(g_tEnnemy[i].pSprite[0], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
		GfxSpriteSetPosition(g_tEnnemy[i].pSprite[1], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
		GfxSpriteSetPosition(g_tEnnemy[i].pSprite[2], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
	}
	for (int i = 0; i < g_iNumberPlayer; ++i)
	{
		g_tPlayer[i].pSpriteSchield = CreateFairy(g_tTexture.pTexture_Shield, g_tPlayer[i].tPosition, 0, 0, 64, 1);
		//GfxSpriteSetColor(g_tPlayer[i].pSpriteSchield, GfxColor(150, 150, 255, 255));
		g_tText.pScore[i] = GfxTextSpriteCreate();
		g_tPlayer[i].tAmmoDepl[i] = TGfxVec2(0, 0);
		g_tPlayer[i].tAmmoPositionInitial[g_tPlayer[i].iAmmoNow] = TGfxVec2(0, 0);
		g_tEvol[i].m_tEvolution = EStateEvol_1;
		g_tMenu.m_tMenu= EStateMenu_principale;
		g_tPlayer[i].tPosition.x = g_tPlayer[i].tPositionInitial.x;
		g_tPlayer[i].tPosition.y = g_tPlayer[i].tPositionInitial.y;
		g_tPlayer[i].pSpriteEvol_1[0] = CreateFairy(g_tTexture.pTexture_16, g_tPlayer[i].tPosition, 0, i * 16, 16, 1);
		g_tPlayer[i].pSpriteEvol_1[1] = CreateFairy(g_tTexture.pTexture_16, g_tPlayer[i].tPosition, 16, i * 16, 16, 1);
		g_tPlayer[i].pSpriteEvol_2[0] = CreateFairy(g_tTexture.pTexture_32, g_tPlayer[i].tPosition, 0, i * 32, 32, 1);
		g_tPlayer[i].pSpriteEvol_2[1] = CreateFairy(g_tTexture.pTexture_32, g_tPlayer[i].tPosition, 32, i * 32, 32, 1);
		g_tPlayer[i].pSpriteEvol_3[0] = CreateFairy(g_tTexture.pTexture_64, g_tPlayer[i].tPosition, 0, i * 64, 64, 1);
		g_tPlayer[i].pSpriteEvol_3[1] = CreateFairy(g_tTexture.pTexture_64, g_tPlayer[i].tPosition, 64, i * 64, 64, 1);
		g_tPlayer[i].pSpriteEvol_4[0] = CreateFairy(g_tTexture.pTexture_128, g_tPlayer[i].tPosition, 0, i * 128, 128, 1);
		g_tPlayer[i].pSpriteEvol_4[1] = CreateFairy(g_tTexture.pTexture_128, g_tPlayer[i].tPosition, 128, i * 128, 128, 1);
		g_tPlayer[i].pSpriteScoring = CreateFairy(g_tTexture.pTexture_128, g_tPlayer[i].tPosition, 128, i * 128, 128, 1);
		g_tPlayer[i].pSpriteEvol_5[0] = CreateFairy(g_tTexture.pTexture_256, g_tPlayer[i].tPosition, 0, i * 256, 256, 1);
		g_tPlayer[i].pSpriteArrow = CreateArrow(g_tTexture.pTexture_Arrow, g_tPlayer[i].tPosition, 32, i * 16, 1);
		for (int j = 0; j < g_iNumberAmmo; j++)
		{
			g_tPlayer[i].pSpriteAmmo[j] = CreateAmmo(g_tTexture.pTexture_Ammo, g_tPlayer[i].tPosition, i * 8, 1);
			GfxSpriteSetAngle(g_tPlayer[i].pSpriteAmmo[j], GfxMathDegToRad(-45));
		}
		g_tPlayer[i].pSpriteBigAmmo = CreateAmmo(g_tTexture.pTexture_Ammo, g_tPlayer[i].tPosition, i * 8, 1);
		GfxSpriteSetAngle(g_tPlayer[i].pSpriteBigAmmo, GfxMathDegToRad(-45));
		GfxSpriteSetScale(g_tPlayer[i].pSpriteBigAmmo, 8, 8);
		g_tPlayer[i].tBigAmmoPositionInitial = TGfxVec2(-128, -128);
		GfxSpriteSetPosition(g_tPlayer[i].pSpriteBigAmmo, g_tPlayer[i].tBigAmmoPositionInitial.x, g_tPlayer[i].tBigAmmoPositionInitial.y);
	}
}

void checkEnnemyCollision(const int iPlayer)
{
	//-----------------------------collision bullet point
	for (int i = 0; i < g_iNumberEnnemyRender; i++)
	{
		for (int j = 0; j < g_iNumberAmmo; j++)
		{
			if (g_tEnnemy[i].pSprite[0] != g_tEnnemy[i].pSprite[1] && g_tEnnemy[i].pSprite[0] != nullptr)
			{
				if (g_tEnnemy[i].tPosition.x - 8 <= g_tPlayer[iPlayer].tAmmoPositionInitial[j].x &&
					g_tEnnemy[i].tPosition.x + 8 >= g_tPlayer[iPlayer].tAmmoPositionInitial[j].x &&
					g_tEnnemy[i].tPosition.y - 8 <= g_tPlayer[iPlayer].tAmmoPositionInitial[j].y &&
					g_tEnnemy[i].tPosition.y + 8 >= g_tPlayer[iPlayer].tAmmoPositionInitial[j].y)
				{
					g_tEnnemy[i].pSprite[0] = g_tEnnemy[i].pSprite[1];
					g_tPlayer[iPlayer].iScore += 5;
				}
			}
		}
	}
	//-----------------------------collision BIG_bullet point
	for (int i = 0; i < g_iNumberEnnemyRender; i++)
	{
		for (int j = 0; j < g_iNumberAmmo; j++)
		{
			if (g_tEnnemy[i].pSprite[0] != g_tEnnemy[i].pSprite[1] && g_tEnnemy[i].pSprite[0] != nullptr)
			{
				if (g_tEnnemy[i].tPosition.x - 32 <= g_tPlayer[iPlayer].tBigAmmoPositionInitial.x &&
					g_tEnnemy[i].tPosition.x + 32 >= g_tPlayer[iPlayer].tBigAmmoPositionInitial.x &&
					g_tEnnemy[i].tPosition.y - 32 <= g_tPlayer[iPlayer].tBigAmmoPositionInitial.y &&
					g_tEnnemy[i].tPosition.y + 32 >= g_tPlayer[iPlayer].tBigAmmoPositionInitial.y)
				{
					g_tEnnemy[i].pSprite[0] = g_tEnnemy[i].pSprite[1];
					g_tPlayer[iPlayer].iScore += 5;
				}
			}
		}
	}
	//-----------------------------collision pitit player vs gros player
	for (int i = 0; i < g_iNumberPlayer; i++)
	{
		for (int j = 0; j < g_iNumberAmmo; j++)
		{
			if (i != iPlayer)
			{
				if (g_tPlayer[iPlayer].tPosition.x <= g_tPlayer[i].tBigAmmoPositionInitial.x + g_tPlayer[iPlayer].fRatio &&
					g_tPlayer[iPlayer].tPosition.x >= g_tPlayer[i].tBigAmmoPositionInitial.x - g_tPlayer[iPlayer].fRatio &&
					g_tPlayer[iPlayer].tPosition.y <= g_tPlayer[i].tBigAmmoPositionInitial.y + g_tPlayer[iPlayer].fRatio &&
					g_tPlayer[iPlayer].tPosition.y >= g_tPlayer[i].tBigAmmoPositionInitial.y - g_tPlayer[iPlayer].fRatio &&
					(g_tPlayer[iPlayer].bActifSchield == false))
				{
					g_tPlayer[iPlayer].iScore --;
					if (g_tPlayer[iPlayer].iScore <= 0)
					{
						g_tPlayer[iPlayer].iScore = 0;
					}
				}
			}
		}
	}
	//-----------------------------collision player VS point
	for (int i = 0; i < g_iNumberEnnemy; i++)
	{
		if (g_tPlayer[iPlayer].tPosition.x - g_tPlayer[iPlayer].fRatio <= g_tEnnemy[i].tPosition.x &&
			g_tPlayer[iPlayer].tPosition.x + g_tPlayer[iPlayer].fRatio >= g_tEnnemy[i].tPosition.x &&
			g_tPlayer[iPlayer].tPosition.y - g_tPlayer[iPlayer].fRatio <= g_tEnnemy[i].tPosition.y &&
			g_tPlayer[iPlayer].tPosition.y + g_tPlayer[iPlayer].fRatio >= g_tEnnemy[i].tPosition.y)
		{
			if (g_tEnnemy[i].pSprite[0] != nullptr && g_tEnnemy[i].pSprite[0] == g_tEnnemy[i].pSprite[1])
			{
				g_tPlayer[iPlayer].iScore += 5;
				g_tEnnemy[i].pSprite[0] = nullptr;
			}
		}
	}
}
void Display()
{
	g_tDisplay.X.iFull = GfxGetDisplaySizeX();
	g_tDisplay.Y.iFull = GfxGetDisplaySizeY();
	g_tDisplay.X.iHalf = g_tDisplay.X.iFull / 2;
	g_tDisplay.Y.iHalf = g_tDisplay.Y.iFull / 2;
	g_tDisplay.X.iQuart = g_tDisplay.X.iFull / 4;
	g_tDisplay.Y.iQuart = g_tDisplay.Y.iFull / 4;
	g_tDisplay.X.iTriQuart = g_tDisplay.X.iQuart * 3;
	g_tDisplay.Y.iTriQuart = g_tDisplay.Y.iQuart * 3;

}
void MovePoint()
{
	for (int i = 0; i < g_iNumberEnnemy; i++)
	{
		if (g_iCounter % 100 == 0)
		{
			g_tEnnemy[i].tDepl = TGfxVec2((GfxMathGetRandomFloat(-1, 1)), (GfxMathGetRandomFloat(-1, 1))).Normalize();
		}

		if ((g_tEnnemy[i].tPosition.x + g_tEnnemy[i].tDepl.x <= 16 && g_tEnnemy[i].tDepl.x < 0) ||
			(g_tEnnemy[i].tPosition.x + g_tEnnemy[i].tDepl.x >= (g_tDisplay.X.iFull - 16) && g_tEnnemy[i].tDepl.x > 0) ||
			(g_tEnnemy[i].tPosition.y + g_tEnnemy[i].tDepl.y <= 16 && g_tEnnemy[i].tDepl.y < 0) ||
			(g_tEnnemy[i].tPosition.y + g_tEnnemy[i].tDepl.y >= (g_tDisplay.Y.iFull - 16) && g_tEnnemy[i].tDepl.y > 0))
		{

		}
		else
		{
			g_tEnnemy[i].tPosition = TGfxVec2(g_tEnnemy[i].tPosition + g_tEnnemy[i].tDepl);
		}
		if (g_tEnnemy[i].pSprite[0] != nullptr)
		{
			GfxSpriteSetPosition(g_tEnnemy[i].pSprite[0], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
			GfxSpriteSetPosition(g_tEnnemy[i].pSprite[1], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
			GfxSpriteSetPosition(g_tEnnemy[i].pSprite[2], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
		}
	}
}
void SetInitialPlayer(const int iPlayer)
{
	if (iPlayer == 0)
	{
		g_tPlayer[iPlayer].tPositionInitial.x = float(g_tDisplay.X.iQuart);
		g_tPlayer[iPlayer].tPositionInitial.y = float(g_tDisplay.Y.iQuart);
	}
	if (iPlayer == 1)
	{
		g_tPlayer[iPlayer].tPositionInitial.x = float(g_tDisplay.X.iTriQuart);
		g_tPlayer[iPlayer].tPositionInitial.y = float(g_tDisplay.Y.iQuart);
	}
	if (iPlayer == 2)
	{
		g_tPlayer[iPlayer].tPositionInitial.x = float(g_tDisplay.X.iQuart);
		g_tPlayer[iPlayer].tPositionInitial.y = float(g_tDisplay.Y.iTriQuart);
	}
	if (iPlayer == 3)
	{
		g_tPlayer[iPlayer].tPositionInitial.x = float(g_tDisplay.X.iTriQuart);
		g_tPlayer[iPlayer].tPositionInitial.y = float(g_tDisplay.Y.iTriQuart);
	}
}
void Controller(const int iPlayer)
{
	float fJoystickLeftX = GfxInputGetPadStickLeftX(iPlayer);
	float fJoystickLeftY = (-1 * GfxInputGetPadStickLeftY(iPlayer));
	float fJoystickRightX = GfxInputGetPadStickRightX(iPlayer);
	float fJoystickRightY = (-1 * GfxInputGetPadStickRightY(iPlayer));

	if (GfxInputIsPressed(EGfxInputID_360PadX, iPlayer) && (GfxInputIsJustPressed(EGfxInputID_360PadY, iPlayer)))
	{
		if (g_bGodMod == true)
		{
			g_bGodMod = false;
		}
		else
		{
			g_bGodMod = true;
		}
	}

	g_tMouvement[iPlayer] = TGfxVec2(fJoystickLeftX, fJoystickLeftY) * g_tPlayer[iPlayer].fSpeed;

	if (fJoystickRightX != 0 && fJoystickRightY != 0)
	{
		g_tDirection[iPlayer] = TGfxVec2(fJoystickRightX, fJoystickRightY).Normalize()* g_tPlayer[iPlayer].fSpeed * 2;
	}
	float fTrigger = GfxInputGetPadTriggerLeft(iPlayer);
	if (fTrigger > 0)
	{
		if (g_tPlayer[iPlayer].bActifSchield == false && g_bSound == true)
		{
			GfxSoundPlay(g_tSound.m_Schield);
		}
		g_tPlayer[iPlayer].bActifSchield = true;
	}
	else
	{
		g_tPlayer[iPlayer].bActifSchield = false;
	}
	//--------BIG
	if (GfxInputIsJustPressed(EGfxInputID_360PadShoulderL, iPlayer) &&
		((g_tPlayer[iPlayer].tBigAmmoPositionInitial.x <= 0 ||
		g_tPlayer[iPlayer].tBigAmmoPositionInitial.y <= 0 )||
		(g_tPlayer[iPlayer].tBigAmmoPositionInitial.x >= g_tDisplay.X.iFull ||
		g_tPlayer[iPlayer].tBigAmmoPositionInitial.y >= g_tDisplay.Y.iFull ))&&
		(g_tPlayer[iPlayer].bActifSchield == false)&&
		(g_tPlayer[iPlayer].iScore >= 5))
	{
		if (g_bSound == true)
		{
			GfxSoundPlay(g_tSound.m_BigShoot);
		}
		g_tPlayer[iPlayer].tBigAmmoPositionInitial = g_tPlayer[iPlayer].tPosition;
		g_tPlayer[iPlayer].tBigAmmoDepl = g_tDirection[iPlayer];
		g_tPlayer[iPlayer].iScore -= 5;
	}
	//--------little
	if (g_bGodMod == false)
	{
		if (GfxInputIsJustPressed(EGfxInputID_360PadShoulderR, iPlayer) && (g_tPlayer[iPlayer].bActifSchield == false))
		{
			if (g_bSound == true)
			{
				GfxSoundPlay(g_tSound.m_Shoot);
			}
			g_tPlayer[iPlayer].tAmmoPositionInitial[g_tPlayer[iPlayer].iAmmoNow] = g_tPlayer[iPlayer].tPosition;
			g_tPlayer[iPlayer].tAmmoDepl[g_tPlayer[iPlayer].iAmmoNow] = g_tDirection[iPlayer];
			g_tPlayer[iPlayer].iAmmoNow++;

			if (g_tPlayer[iPlayer].iAmmoNow >= g_iNumberAmmo)
			{
				g_tPlayer[iPlayer].iAmmoNow = 0;
			}
		}
	}
	else
	{
		if (GfxInputIsPressed(EGfxInputID_360PadShoulderR, iPlayer) && (g_tPlayer[iPlayer].bActifSchield == false))
		{

			if (g_iCounter % 5 == 0 && g_bSound == true)
			{
			GfxSoundPlay(g_tSound.m_Shoot);
			}
			g_tPlayer[iPlayer].tAmmoPositionInitial[g_tPlayer[iPlayer].iAmmoNow] = g_tPlayer[iPlayer].tPosition;
			g_tPlayer[iPlayer].tAmmoDepl[g_tPlayer[iPlayer].iAmmoNow] = g_tDirection[iPlayer];
			g_tPlayer[iPlayer].iAmmoNow++;

			if (g_tPlayer[iPlayer].iAmmoNow >= g_iNumberAmmo)
			{
				g_tPlayer[iPlayer].iAmmoNow = 0;
			}
		}
	}
	//------------
	float hypothenuse = g_tDirection[iPlayer].Length();
	float fAngle;

	if (g_tDirection[iPlayer].y <= 0)
	{
		fAngle = GfxMathRadToDeg(acos(g_tDirection[iPlayer].x / hypothenuse));
	}
	else
	{
		fAngle = -1 * (GfxMathRadToDeg(acos(g_tDirection[iPlayer].x / hypothenuse)));
	}
	if (g_tPlayer[iPlayer].tPosition.x + g_tMouvement[iPlayer].x >= 0 &&
		g_tPlayer[iPlayer].tPosition.y + g_tMouvement[iPlayer].y >= 0 &&
		g_tPlayer[iPlayer].tPosition.x + g_tMouvement[iPlayer].x <= g_tDisplay.X.iFull &&
		g_tPlayer[iPlayer].tPosition.y + g_tMouvement[iPlayer].y <= g_tDisplay.Y.iFull)
	{
		//-----------------------------collision player VS pointNoir
		for (int i = 0; i < g_iNumberEnnemyRender; i++)
		{
			if (g_tPlayer[iPlayer].tPosition.x<= g_tEnnemy[i].tPosition.x + 16 &&
				g_tPlayer[iPlayer].tPosition.x>= g_tEnnemy[i].tPosition.x - 16 &&
				g_tPlayer[iPlayer].tPosition.y<= g_tEnnemy[i].tPosition.y + 16 &&
				g_tPlayer[iPlayer].tPosition.y>= g_tEnnemy[i].tPosition.y - 16)
			{
				if (g_tEnnemy[i].pSprite[0] != nullptr && g_tEnnemy[i].pSprite[0] != g_tEnnemy[i].pSprite[1])
				{
					g_tMouvement[iPlayer] *= -1;
					//g_tEnnemy[i].pSprite[0] = nullptr;
				}
			}
		}
		g_tPlayer[iPlayer].tPosition += g_tMouvement[iPlayer];
	}
	GfxSpriteSetPivot(g_tPlayer[iPlayer].pSpriteArrow, -g_tPlayer[iPlayer].fRatio,8);
	GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteArrow, g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
	GfxSpriteSetAngle(g_tPlayer[iPlayer].pSpriteArrow, GfxMathDegToRad(fAngle));
	GfxSpriteSetAngle(g_tPlayer[iPlayer].pSpriteAmmo[g_tPlayer[iPlayer].iAmmoNow], GfxMathDegToRad(fAngle - 45));
	GfxSpriteSetAngle(g_tPlayer[iPlayer].pSpriteBigAmmo, GfxMathDegToRad(fAngle - 45));

	//GfxDbgPrintf("%f\n", fAngle);

}
void SpriteVsEvol(const int iPlayer)
{
	if (GfxInputIsJustPressed(EGfxInputID_360PadB, iPlayer))
	{
		//CHEAT
	//	g_tPlayer[iPlayer].iScore += 100;
	}
	for (int j = 0; j < g_iNumberAmmo; j++)
	{
		g_tPlayer[iPlayer].tAmmoPositionInitial[j].y += g_tPlayer[iPlayer].tAmmoDepl[j].y;
		g_tPlayer[iPlayer].tAmmoPositionInitial[j].x += g_tPlayer[iPlayer].tAmmoDepl[j].x;
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteAmmo[j], g_tPlayer[iPlayer].tAmmoPositionInitial[j].x, g_tPlayer[iPlayer].tAmmoPositionInitial[j].y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteSchield, g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
	}
	g_tPlayer[iPlayer].tBigAmmoPositionInitial.y += g_tPlayer[iPlayer].tBigAmmoDepl.y;
	g_tPlayer[iPlayer].tBigAmmoPositionInitial.x += g_tPlayer[iPlayer].tBigAmmoDepl.x;
	GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteBigAmmo, g_tPlayer[iPlayer].tBigAmmoPositionInitial.x, g_tPlayer[iPlayer].tBigAmmoPositionInitial .y);

	switch (g_tEvol[iPlayer].m_tEvolution)
	{
	case EStateEvol_1:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_1[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_1[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (g_tPlayer[iPlayer].iScore >= 50)
		{
			if (g_bSound == true)
			{
				GfxSoundPlay(g_tSound.m_Evol);
			}
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_2;
			g_tPlayer[iPlayer].iScore -= 50;
			g_tPlayer[iPlayer].fRatio *= 2;
			GfxSpriteSetPivot(g_tPlayer[iPlayer].pSpriteArrow, g_tPlayer[iPlayer].fRatio, 8);
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 1.5f, 1.5f);
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteSchield, 2, 2);
			}
		}
		break;
	case EStateEvol_2:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_2[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_2[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if ( g_tPlayer[iPlayer].iScore >= 100)
		{
			if (g_bSound == true)
			{
				GfxSoundPlay(g_tSound.m_Evol);
			}
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_3;
			g_tPlayer[iPlayer].iScore -= 100;
			g_tPlayer[iPlayer].fRatio *= 2;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 2, 2);
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteSchield, 3, 3);
			}
		}
		break;
	case EStateEvol_3:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_3[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_3[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (g_tPlayer[iPlayer].iScore >= 150)
		{
			if (g_bSound == true)
			{
				GfxSoundPlay(g_tSound.m_Evol);
			}
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_4;
			g_tPlayer[iPlayer].iScore -= 150;
			g_tPlayer[iPlayer].fRatio *= 2;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 2.5f, 2.5f);
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteSchield, 4, 4);
			}
		}
		break;
	case EStateEvol_4:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_4[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_4[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (g_tPlayer[iPlayer].iScore >= 200)
		{
			if (g_bSound == true)
			{
				GfxSoundPlay(g_tSound.m_Evol);
			}
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_5;
			g_tPlayer[iPlayer].iScore -= 200;
			g_tPlayer[iPlayer].fRatio *= 2;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 3, 3);
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteSchield, 10, 10);
			}
		}
		break;
	case EStateEvol_5:
		if (g_tPlayer[iPlayer].tPosition.x >= g_tWinnerPos[iPlayer].x - 10 &&
			g_tPlayer[iPlayer].tPosition.x <= g_tWinnerPos[iPlayer].x + 10 &&
			g_tPlayer[iPlayer].tPosition.y >= g_tWinnerPos[iPlayer].y - 10 &&
			g_tPlayer[iPlayer].tPosition.y <= g_tWinnerPos[iPlayer].y + 10)
		{

		}
		else
		{
		g_tPlayer[iPlayer].tPosition += TGfxVec2(g_tWinnerPos[iPlayer] - g_tPlayer[iPlayer].tPosition).Normalize()* 5;
		}
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_5[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		/*if (g_tPlayer[iPlayer].iScore >= 250)
		{
			GfxSoundPlay(g_tSound.m_Evol);

			g_tEvol[iPlayer].m_tEvolution = EStateEvol_1;
			g_tPlayer[iPlayer].iScore = 0;
			g_tPlayer[iPlayer].fRatio /= 8;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 4, 4);
			}
		}*/	
		break;
	default:
		break;
	}
}
void RenderVsEvol(const int iPlayer)
{
	switch (g_tEvol[iPlayer].m_tEvolution)
	{
	case EStateEvol_1:
		GfxSpriteRender(g_tPlayer[iPlayer].pSpriteEvol_1[g_tPlayer[iPlayer].iFrame]);
		break;
	case EStateEvol_2:
		GfxSpriteRender(g_tPlayer[iPlayer].pSpriteEvol_2[g_tPlayer[iPlayer].iFrame]);

		break;
	case EStateEvol_3:
		GfxSpriteRender(g_tPlayer[iPlayer].pSpriteEvol_3[g_tPlayer[iPlayer].iFrame]);

		break;
	case EStateEvol_4:
		GfxSpriteRender(g_tPlayer[iPlayer].pSpriteEvol_4[g_tPlayer[iPlayer].iFrame]);

		break;
	case EStateEvol_5:
		GfxSpriteRender(g_tPlayer[iPlayer].pSpriteEvol_5[0]);

		break;
	default:
		break;
	}
}
void setScoring()
{
	for (int i = 0; i < g_iNumberPlayer; i++)
	{
		GfxTextSpritePrintf(g_tText.pScore[i]," :%i",g_tPlayer[i].iScore);
	}
}

void MenuUpdate()
{
	//controller


	if (GfxInputIsJustPressed(EGfxInputID_360PadUp) && g_iWitchIsChoose > 1)
	{
		g_iWitchIsChoose--;
	}
	if (GfxInputIsJustPressed(EGfxInputID_360PadDown) && g_iWitchIsChoose < 3)
	{
		g_iWitchIsChoose++;
	}
	//mousse
	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		if ((GfxGetCurrentMouseX() >= (g_tDisplay.X.iQuart / 3)) &&
			(GfxGetCurrentMouseX() <= (g_tDisplay.X.iQuart / 3) + 256) &&
			(GfxGetCurrentMouseY() >= (g_tDisplay.Y.iQuart / 2)) &&
			(GfxGetCurrentMouseY() <= (g_tDisplay.Y.iQuart / 2) + 128))
		{
			g_tMenu.m_tMenu = EStateMenu_Ingame;
		}
		if ((GfxGetCurrentMouseX() >= (g_tDisplay.X.iQuart / 3)) &&
			(GfxGetCurrentMouseX() <= (g_tDisplay.X.iQuart / 3) + 256) &&
			(GfxGetCurrentMouseY() >= (g_tDisplay.Y.iHalf)) &&
			(GfxGetCurrentMouseY() <= (g_tDisplay.Y.iHalf) + 128))
		{
			g_tMenu.m_tMenu = EStateMenu_tuto;
		}
		if ((GfxGetCurrentMouseX() >= (g_tDisplay.X.iQuart / 3)) &&
			(GfxGetCurrentMouseX() <= (g_tDisplay.X.iQuart / 3) + 256) &&
			(GfxGetCurrentMouseY() >= (g_tDisplay.Y.iTriQuart)) &&
			(GfxGetCurrentMouseY() <= (g_tDisplay.Y.iTriQuart) + 128))
		{
			GfxExitRequest();
		}
	}
	if (g_iWitchIsChoose == 1)
	{
		if (GfxInputIsJustPressed(EGfxInputID_360PadA))
		{
			g_tMenu.m_tMenu = EStateMenu_Ingame;
		}
	}
	if (g_iWitchIsChoose == 2)
	{
		if (GfxInputIsJustPressed(EGfxInputID_360PadA))
		{
			g_tMenu.m_tMenu = EStateMenu_tuto;
		}
	}
	if (g_iWitchIsChoose == 3)
	{
		if (GfxInputIsJustPressed(EGfxInputID_360PadA))
		{
			GfxExitRequest();
		}
	}


}
void TutoUpdate()
{
	if (GfxInputIsJustPressed(EGfxInputID_360PadRight) && g_iNumberTuto < (g_iNumberTutotPage-1))
	{
		g_iNumberTuto++;
	}
	if (GfxInputIsJustPressed(EGfxInputID_360PadLeft) && g_iNumberTuto > 0)
	{
		g_iNumberTuto--;
	}
	if (GfxInputIsJustPressed(EGfxInputID_360PadStart))
	{
		g_tMenu.m_tMenu = EStateMenu_principale;
	}
}
void IngameUpdate()
{
	g_bPlayAmb = false;

	setScoring();
	clock();
	MovePoint();
	g_iCounter++;
	g_iNumberPlayerInGame = CheckPad();

	if (checkAllPlayerWin() == true)
	{
		g_tMenu.m_tMenu = EStateMenu_principale;
	}
	if (GfxInputIsJustPressed(EGfxInputID_360PadStart))
	{
		g_tMenu.m_tMenu = EStateMenu_principale;
	}
	for (int i = 0; i < g_iNumberGlow; ++i)
	{
		GfxSpriteSetPosition(g_tGlow[i].pSprite[0], (g_tGlow[i].tPosition.x + cos(GfxMathDegToRad(g_tGlow[i].fAngle)) * 250), (g_tGlow[i].tPosition.y + sin(GfxMathDegToRad(g_tGlow[i].fAngle)) * 250));
		g_tGlow[i].fAngle++;
	}
	for (int i = 0; i < g_iNumberPlayer; i++)
	{
		SpriteVsEvol(i);
	}
	if (checkAllDead() == false)
	{
		for (int i = 0; i < g_iNumberEnnemy; i++)
		{
			g_tEnnemy[i].pSprite[0] = g_tEnnemy[i].pSprite[2];
			g_tEnnemy[i].tPosition = TGfxVec2(float(GfxMathGetRandomInteger(16, g_tDisplay.X.iFull - 16)), float(GfxMathGetRandomInteger(16, g_tDisplay.Y.iFull - 16)));
			GfxSpriteSetPosition(g_tEnnemy[i].pSprite[0], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
			GfxSpriteSetPosition(g_tEnnemy[i].pSprite[1], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
			GfxSpriteSetPosition(g_tEnnemy[i].pSprite[2], g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
			g_iNumberEnnemyRender = 0;
		}
	}
	if (g_iCounter % 10 == 0)
	{
		for (int i = 0; i < g_iNumberPlayer; i++)
		{
			if (g_tPlayer[i].iFrame > 0)
			{
				g_tPlayer[i].iFrame--;
			}
			else
			{
				g_tPlayer[i].iFrame++;
			}
		}
	}
	if (g_tClock.fBetween >= (4000 / (g_iNumberPlayerInGame + 1)))
	{
		g_tClock.fOld = GfxTimeGetMilliseconds();
		if (g_iNumberEnnemyRender != g_iNumberEnnemy)
		{
			g_iNumberEnnemyRender++;
		}
	}
	for (int i = 0; i < g_iNumberPlayer; i++)
	{
		checkEnnemyCollision(i);
	}
	for (int i = 0; i < g_iNumberPlayerInGame; i++)
	{
		Controller(i);
	}
}

void MenuRender()
{
	GfxSpriteRender(g_tMenuSprite[0].pSpriteBackground);
	GfxSpriteRender(g_tMenuSprite[0].pSpriteTitle);

	if (g_iWitchIsChoose == 1)
	{
		GfxSpriteRender(g_tMenuSprite[1].pSpritePlay);

	}
	else
	{
		GfxSpriteRender(g_tMenuSprite[0].pSpritePlay);

	}
	if (g_iWitchIsChoose == 2)
	{
		GfxSpriteRender(g_tMenuSprite[1].pSpriteExit);
	}
	else
	{
		GfxSpriteRender(g_tMenuSprite[0].pSpriteExit);
	}
	if (g_iWitchIsChoose == 3)
	{
		GfxSpriteRender(g_tMenuSprite[1].pSpriteTutoriel);
	}
	else
	{
		GfxSpriteRender(g_tMenuSprite[0].pSpriteTutoriel);

	}

}
void TutoRender()
{
	GfxSpriteRender(g_tTuto[g_iNumberTuto].pSprite);
}
void IngameRender()
{

	for (int i = 0; i < g_iNumberGlow; i++)
	{
		GfxSpriteRender(g_tGlow[i].pSprite[0]);
	}
	for (int i = 0; i < g_iNumberEnnemyRender; i++)
	{
		if (g_tEnnemy[i].pSprite[0] != nullptr)
		{

			GfxSpriteRender(g_tEnnemy[i].pSprite[0]);
		}
	}
	for (int i = 0; i < g_iNumberPlayerInGame; i++)
	{
		for (int j = 0; j < g_iNumberAmmo; j++)
		{
			GfxSpriteRender(g_tPlayer[i].pSpriteAmmo[j]);
		}
		GfxSpriteRender(g_tPlayer[i].pSpriteBigAmmo);
		GfxSpriteRender(g_tPlayer[i].pSpriteArrow);
		RenderVsEvol(i);
		GfxTextSpriteRender(g_tText.pScore[i], 32.0f, float(32 * (i + 1)), EGfxColor_White, 3, false, true);

		GfxSpriteRender(g_tPlayer[i].pSpriteScoring);
		if (g_tPlayer[i].bActifSchield == true)
		{
			GfxSpriteRender(g_tPlayer[i].pSpriteSchield);
		}
	}
	if (g_bGodMod == true)
	{
		GfxTextSpriteRender(g_pTextGod,float( g_tDisplay.X.iTriQuart), float (GfxSpriteGetSizeY(g_pTextGod)), EGfxColor_White, 3, true, false);
	}

}

void Initialize()
{
	g_tClock.fOld = GfxTimeGetMilliseconds();
	Display();
	g_tSound.m_Shoot = CreateSound("Wave_1.wav");
	//g_tSound.m_Schield= CreateSound("Wave_2.wav");
	g_tSound.m_Schield = CreateSound("Wave_3.wav");
	g_tSound.m_BigShoot = CreateSound("Wave_4.wav");
	//g_tSound.m_ = CreateSound("Wave_5.wav");
	g_tSound.m_Evol = CreateSound("Wave_6.wav");
//	g_tSound.m_Ambience = CreateSound("menu100.wav");

	for (int i = 0; i < g_iNumberPlayer; i++)
	{
		g_tWinnerPos[i] = TGfxVec2(float(g_tDisplay.X.iFull - 50), float(g_tDisplay.Y.iQuart *(i + 1) - 64));
	}

	g_pTextGod = GfxTextSpriteCreate();
	GfxTextSpritePrintf(g_pTextGod, "GodMod Activated");
	GfxSpriteSetFilteringEnabled(g_pTextGod, false);
	g_pTextMusique= GfxTextSpriteCreate();
	GfxTextSpritePrintf(g_pTextMusique, "Musique:on");
	GfxSpriteSetFilteringEnabled(g_pTextMusique, false);

	for (int i = 0; i < g_iNumberPlayer; ++i)
	{
		SetInitialPlayer(i);
	}
	createSprite();
	for (int i = 0; i < g_iNumberPlayer; ++i)
	{
		GfxSpriteSetScale(g_tPlayer[i].pSpriteScoring, 0.25f, 0.25f);
		GfxSpriteSetFilteringEnabled(g_tText.pScore[i], false);
		GfxSpriteSetPosition(g_tPlayer[i].pSpriteScoring, 32.0f, float (32 * (i + 1)));
	}
}
void Update()
{
	if (GfxInputIsJustPressed(EGfxInputID_360PadBack))
	{
		if (g_bSound == true)
		{
			g_bSound = false;
			GfxTextSpritePrintf(g_pTextMusique, "Musique:off");
		}
		else
		{
			g_bSound = true;
			GfxTextSpritePrintf(g_pTextMusique, "Musique:on");
		}
	}
	switch (g_tMenu.m_tMenu)
	{
	case EStateMenu_principale:
		MenuUpdate();
		break;
	case EStateMenu_tuto:
		TutoUpdate();
		break;
	case EStateMenu_Ingame:
		IngameUpdate();
		break;

	default:
		break;
	}

}
void Render()
{
	GfxClear(GfxColor(0,30,0,255));
	switch (g_tMenu.m_tMenu)
	{
	case EStateMenu_principale:
		MenuRender();
		break;
	case EStateMenu_tuto:
		TutoRender();
		break;
	case EStateMenu_Ingame:
		IngameRender();
		break;

	default:
		break;
	}
	GfxTextSpriteRender(g_pTextMusique, float(g_tDisplay.X.iTriQuart + GfxSpriteGetSizeX(g_pTextGod)), float(g_tDisplay.Y.iFull - GfxSpriteGetSizeY(g_pTextMusique) * 3), EGfxColor_White, 1, true, false);
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
	GfxDefaultResolution(1280,1024);

}