#include "flib.h"
#include "flib_vec2.h"
#include <math.h>
#include "Header.h"
#include "NotVoid.h"

const int g_iNumber = 0;

void checkEnnemyCollision(const int iPlayer)
{
	for (int i = 0; i < g_iNumberEnnemy; i++)
	{
		for (int j = 0; j < g_iNumberAmmo; j++)
		{
			if (g_tEnnemy[i].tPosition.x - 8 <= g_tPlayer[iPlayer].tAmmoPositionInitial[j].x &&
				g_tEnnemy[i].tPosition.x + 8 >= g_tPlayer[iPlayer].tAmmoPositionInitial[j].x &&
				g_tEnnemy[i].tPosition.y - 8 <= g_tPlayer[iPlayer].tAmmoPositionInitial[j].y &&
				g_tEnnemy[i].tPosition.y + 8 >= g_tPlayer[iPlayer].tAmmoPositionInitial[j].y)
			{
				g_tEnnemy[i].pSprite = nullptr;
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
	if (GfxInputIsJustPressed(EGfxInputID_360PadShoulderR, iPlayer))
	{
		g_tPlayer[iPlayer].tAmmoPositionInitial[g_tPlayer[iPlayer].iAmmoNow] = g_tPlayer[iPlayer].tPosition;
		g_tPlayer[iPlayer].tAmmoDepl[g_tPlayer[iPlayer].iAmmoNow] = g_tDirection[iPlayer];
		g_tPlayer[iPlayer].iAmmoNow ++;

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

	GfxDbgPrintf("%f\n", fAngle);

}
void SpriteVsEvol(const int iPlayer)
{
	for (int j = 0; j < g_iNumberAmmo; j++)
	{
		g_tPlayer[iPlayer].tAmmoPositionInitial[j].y += g_tPlayer[iPlayer].tAmmoDepl[j].y;
		g_tPlayer[iPlayer].tAmmoPositionInitial[j].x += g_tPlayer[iPlayer].tAmmoDepl[j].x;
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteAmmo[j], g_tPlayer[iPlayer].tAmmoPositionInitial[j].x, g_tPlayer[iPlayer].tAmmoPositionInitial[j].y);
	}
	switch (g_tEvol[iPlayer].m_tEvolution)
	{
	case EStateEvol_1:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_1[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_1[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (GfxInputIsJustPressed(EGfxInputID_KeySpace))
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_2;
		}
		break;
	case EStateEvol_2:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_2[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_2[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (GfxInputIsJustPressed(EGfxInputID_KeySpace))
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_3;
		}
		break;
	case EStateEvol_3:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_3[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_3[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (GfxInputIsJustPressed(EGfxInputID_KeySpace))
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_4;
		}
		break;
	case EStateEvol_4:
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_4[0], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		GfxSpriteSetPosition(g_tPlayer[iPlayer].pSpriteEvol_4[1], g_tPlayer[iPlayer].tPosition.x, g_tPlayer[iPlayer].tPosition.y);
		if (GfxInputIsJustPressed(EGfxInputID_KeySpace))
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_5;
		}
		break;
	case EStateEvol_5:
		if (GfxInputIsJustPressed(EGfxInputID_KeySpace))
		{
			g_tEvol[iPlayer].m_tEvolution = EStateEvol_1;
		}		break;
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

		break;
	default:
		break;
	}
}

void Initialize()
{

	g_tTexture.pTexture_16 = CreateTexture("fairy_16.tga");
	g_tTexture.pTexture_32 = CreateTexture("fairy_32.tga");
	g_tTexture.pTexture_64 = CreateTexture("fairy_64.tga");
	g_tTexture.pTexture_128 = CreateTexture("fairy_128.tga");
	g_tTexture.pTexture_Arrow = CreateTexture("arrow.tga");
	g_tTexture.pTexture_Ammo = CreateTexture("ammo.tga");
	g_tTexture.pTexture_Ennemy= CreateTexture("fairy_16.tga");

	Display();
	for (int i = 0; i < g_iNumberEnnemy; ++i)
	{
		g_tEnnemy[i].pSprite = CreateFairy(g_tTexture.pTexture_Ennemy, g_tEnnemy[i].tPosition,0,48,16,1);
		g_tEnnemy[i].tPosition = TGfxVec2(float(GfxMathGetRandomInteger(16, g_tDisplay.X.iFull - 16)), float(GfxMathGetRandomInteger(16, g_tDisplay.Y.iFull - 16)));
		GfxSpriteSetPosition(g_tEnnemy[i].pSprite, g_tEnnemy[i].tPosition.x, g_tEnnemy[i].tPosition.y);
	}
	for (int i = 0; i < g_iNumberPlayer; ++i)
	{
		g_tPlayer[i].tAmmoDepl[i] = TGfxVec2(0, 0);
		g_tPlayer[i].tAmmoPositionInitial[g_tPlayer[i].iAmmoNow]= TGfxVec2(0, 0);
		g_tEvol[i].m_tEvolution = EStateEvol_1;
		SetInitialPlayer(i);
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
		g_tPlayer[i].pSpriteArrow = CreateArrow(g_tTexture.pTexture_Arrow, g_tPlayer[i].tPosition, 32, i * 16, 1);

		for (int j = 0; j < g_iNumberAmmo; j++)
		{
			g_tPlayer[i].pSpriteAmmo[j] = CreateAmmo(g_tTexture.pTexture_Ammo, g_tPlayer[i].tPosition, i * 8, 1);
			GfxSpriteSetAngle(g_tPlayer[i].pSpriteAmmo[j], GfxMathDegToRad(-45));
		}
	}
}
void Update()
{
	g_iCounter++;
	for (int i = 0; i < g_iNumberPlayer; i++)
	{
		SpriteVsEvol(i);
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
	g_iNumberPlayerInGame = CheckPad();
	for (int i = 0; i < g_iNumberPlayer; i++)
	{
		checkEnnemyCollision(i);
	}



	//GfxDbgPrintf("Il y a %i manette de connect�\nPosx -- %f\nPosy -- %f\n", g_iNumberPlayerInGame, g_tPlayer[0].tPosition.x, g_tPlayer[0].tPosition.y);

	for (int i = 0; i < g_iNumberPlayerInGame; i++)
	{
		Controller(i);
	}

}
void Render()
{
	GfxClear(EGfxColor_Black);
	for (int i = 0; i < g_iNumberEnnemy; i++)
	{
		if (g_tEnnemy[i].pSprite != nullptr)
		{
			GfxSpriteRender(g_tEnnemy[i].pSprite);
		}
	}
	for (int i = 0; i < g_iNumberPlayerInGame; i++)
	{
		for (int j = 0; j < g_iNumberAmmo; j++)
		{
		GfxSpriteRender(g_tPlayer[i].pSpriteAmmo[j]);
		}
		GfxSpriteRender(g_tPlayer[i].pSpriteArrow);
		RenderVsEvol(i);
	}
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
	//GfxDefaultResolution(1500, 800);
}