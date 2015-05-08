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
	g_tTexture.pTexture_Shield= CreateTexture("glow.tga");

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
		g_tPlayer[i].pSpriteSchield = CreateFairy(g_tTexture.pTexture_Shield, g_tPlayer[i].tPosition, 0, 0, 256, 0.5f);
		GfxSpriteSetColor(g_tPlayer[i].pSpriteSchield, GfxColor(150, 150, 255, 255));
		g_tText.pScore[i] = GfxTextSpriteCreate();
		g_tPlayer[i].tAmmoDepl[i] = TGfxVec2(0, 0);
		g_tPlayer[i].tAmmoPositionInitial[g_tPlayer[i].iAmmoNow] = TGfxVec2(0, 0);
		g_tEvol[i].m_tEvolution = EStateEvol_1;
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
				if (g_tPlayer[iPlayer].tPosition.x <= g_tPlayer[i].tBigAmmoPositionInitial.x + g_tPlayer[i].fRatio &&
					g_tPlayer[iPlayer].tPosition.x >= g_tPlayer[i].tBigAmmoPositionInitial.x - g_tPlayer[i].fRatio &&
					g_tPlayer[iPlayer].tPosition.y <= g_tPlayer[i].tBigAmmoPositionInitial.y + g_tPlayer[i].fRatio &&
					g_tPlayer[iPlayer].tPosition.y >= g_tPlayer[i].tBigAmmoPositionInitial.y - g_tPlayer[i].fRatio &&
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

	g_tMouvement[iPlayer] = TGfxVec2(fJoystickLeftX, fJoystickLeftY) * g_tPlayer[iPlayer].fSpeed;

	if (fJoystickRightX != 0 && fJoystickRightY != 0)
	{
		g_tDirection[iPlayer] = TGfxVec2(fJoystickRightX, fJoystickRightY).Normalize()* g_tPlayer[iPlayer].fSpeed * 2;
	}
	float fTrigger = GfxInputGetPadTriggerLeft(iPlayer);
	if (fTrigger > 0)
	{
		g_tPlayer[iPlayer].bActifSchield = true;
	}
	else
	{
		g_tPlayer[iPlayer].bActifSchield = false;
	}

	if (GfxInputIsJustPressed(EGfxInputID_360PadShoulderL, iPlayer) &&
		((g_tPlayer[iPlayer].tBigAmmoPositionInitial.x <= 0 ||
		g_tPlayer[iPlayer].tBigAmmoPositionInitial.y <= 0 )||
		(g_tPlayer[iPlayer].tBigAmmoPositionInitial.x >= g_tDisplay.X.iFull ||
		g_tPlayer[iPlayer].tBigAmmoPositionInitial.y >= g_tDisplay.Y.iFull ))&&
		(g_tPlayer[iPlayer].bActifSchield == false)&&
		(g_tPlayer[iPlayer].iScore >= 5))
	{
		g_tPlayer[iPlayer].tBigAmmoPositionInitial = g_tPlayer[iPlayer].tPosition;
		g_tPlayer[iPlayer].tBigAmmoDepl = g_tDirection[iPlayer];
		g_tPlayer[iPlayer].iScore -= 5;
	}
	if (GfxInputIsJustPressed(EGfxInputID_360PadShoulderR, iPlayer) && (g_tPlayer[iPlayer].bActifSchield == false))
	{
		g_tPlayer[iPlayer].tAmmoPositionInitial[g_tPlayer[iPlayer].iAmmoNow] = g_tPlayer[iPlayer].tPosition;
		g_tPlayer[iPlayer].tAmmoDepl[g_tPlayer[iPlayer].iAmmoNow] = g_tDirection[iPlayer];
		g_tPlayer[iPlayer].iAmmoNow++;

		if (g_tPlayer[iPlayer].iAmmoNow >= g_iNumberAmmo)
		{
			g_tPlayer[iPlayer].iAmmoNow = 0;
		}
	}

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
		g_tPlayer[iPlayer].tPosition += g_tMouvement[iPlayer];
	}

	GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteArrow, g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
	GfxSpriteSetAngle(g_tPlayer[iPlayer].pSpriteArrow, GfxMathDegToRad(fAngle));
	GfxSpriteSetAngle(g_tPlayer[iPlayer].pSpriteAmmo[g_tPlayer[iPlayer].iAmmoNow], GfxMathDegToRad(fAngle - 45));
	GfxSpriteSetAngle(g_tPlayer[iPlayer].pSpriteBigAmmo, GfxMathDegToRad(fAngle - 45));

	//GfxDbgPrintf("%f\n", fAngle);

}
void SpriteVsEvol(const int iPlayer)
{
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
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_2;
			g_tPlayer[iPlayer].iScore -= 50;
			g_tPlayer[iPlayer].fRatio *= 2;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 1.5f, 1.5f);
			}
		}
		break;
	case EStateEvol_2:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_2[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_2[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if ( g_tPlayer[iPlayer].iScore >= 100)
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_3;
			g_tPlayer[iPlayer].iScore -= 100;
			g_tPlayer[iPlayer].fRatio *= 2;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 2, 2);
			}
		}
		break;
	case EStateEvol_3:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_3[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_3[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (g_tPlayer[iPlayer].iScore >= 150)
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_4;
			g_tPlayer[iPlayer].iScore -= 150;
			g_tPlayer[iPlayer].fRatio *= 2;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 2.5f, 2.5f);
			}
		}
		break;
	case EStateEvol_4:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_4[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_4[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (g_tPlayer[iPlayer].iScore >= 200)
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_5;
			g_tPlayer[iPlayer].iScore -= 200;
			g_tPlayer[iPlayer].fRatio *= 2;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 3, 3);
			}
		}
		break;
	case EStateEvol_5:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_5[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (g_tPlayer[iPlayer].iScore >= 250)
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_1;
			g_tPlayer[iPlayer].iScore = 0;
			for (int i = 0; i < g_iNumberAmmo; i++)
			{
				GfxSpriteSetScale(g_tPlayer[iPlayer].pSpriteAmmo[i], 4, 4);
			}
		}	
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
		GfxTextSpritePrintf(g_tText.pScore[i]," :%i   %i",g_tPlayer[i].iScore,(g_tEvol[i].m_tEvolution * 50));
	}
}

void Initialize()
{
	g_tClock.fOld = GfxTimeGetMilliseconds();
	Display();
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
	setScoring();
	clock();
	MovePoint();
	g_iCounter++;
	if (GfxInputIsJustPressed(EGfxInputID_360PadStart))
	{
		GfxExitRequest();
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
	if (g_tClock.fBetween >= (4000/(g_iNumberPlayerInGame + 1)))
	{
		g_tClock.fOld = GfxTimeGetMilliseconds();
		g_iNumberEnnemyRender++;
	}
	g_iNumberPlayerInGame = CheckPad();
	for (int i = 0; i < g_iNumberPlayer; i++)
	{
		checkEnnemyCollision(i);
	}
	for (int i = 0; i < g_iNumberPlayerInGame; i++)
	{
		Controller(i);
	}
}
void Render()
{
	GfxClear(GfxColor(0,30,0,255));
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
		GfxTextSpriteRender(g_tText.pScore[i], 32.0f, float (32 * (i + 1)), EGfxColor_White, 3, false, true);
		
		GfxSpriteRender(g_tPlayer[i].pSpriteScoring);
		if (g_tPlayer[i].bActifSchield == true)
		{
			GfxSpriteRender(g_tPlayer[i].pSpriteSchield);
		}
	}

}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
	GfxDefaultResolution(1500, 700);
}