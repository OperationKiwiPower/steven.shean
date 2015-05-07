#include "flib.h"
#include "flib_vec2.h"
#include <math.h>
#include "Header.h"
#include "NotVoid.h"

const int g_iNumber = 0;

void Display()
{
	g_tDisplay.X.iFull = GfxGetDisplaySizeX();
	g_tDisplay.Y.iFull = GfxGetDisplaySizeX();
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
		g_tPlayer[iPlayer].tPositionInitial.x = float(g_tDisplay.X.iQuart);
		g_tPlayer[iPlayer].tPositionInitial.y = float(g_tDisplay.Y.iTriQuart);
	}
	if (iPlayer == 2)
	{
		g_tPlayer[iPlayer].tPositionInitial.x = float(g_tDisplay.X.iTriQuart);
		g_tPlayer[iPlayer].tPositionInitial.y = float(g_tDisplay.Y.iQuart);
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

	g_tMouvement = TGfxVec2(fJoystickLeftX, fJoystickLeftY) * g_tPlayer[iPlayer].fSpeed;

	if (fJoystickRightX != 0 && fJoystickRightY != 0)
	{
		g_tDirection = TGfxVec2(fJoystickRightX, fJoystickRightY).Normalize()* g_tPlayer[iPlayer].fSpeed * 2;
	}


	g_tPlayer[iPlayer].tPosition += g_tMouvement;

	if (g_tPlayer[iPlayer].tPosition != g_tMousse.tMousse)
	{
		g_tPlayer[iPlayer].pSprite = DrawLine(g_tPlayer[iPlayer].pSprite, g_tPlayer[iPlayer].tPosition, g_tDirection, g_tPlayer[iPlayer].fRatio);
	}

	//GfxDbgPrintf("%f__%f\n", fJoystickX, fJoystickY);

}

void Initialize()
{
	Display();
	for (int i = 0; i < g_iNumberPlayer; ++i)
	{
		SetInitialPlayer(i);
		g_tPlayer[i].tPosition.x = g_tPlayer[i].tPositionInitial.x;
		g_tPlayer[i].tPosition.y = g_tPlayer[i].tPositionInitial.y;
		g_tPlayer[i].pSprite = GfxLineSpriteCreate();
		GfxLineSpriteSetDrawingColor(g_tPlayer[i].pSprite, EGfxColor_White);
	}

}
void Update()
{
	g_tMousse.tMousse = TGfxVec2(float(GfxGetCurrentMouseX()), float (GfxGetCurrentMouseY()));

	g_iNumberPlayerInGame = CheckPad();
	
	//GfxDbgPrintf("Il y a %i manette de connecté\nPosx -- %f\nPosy -- %f\n", g_iNumberPlayerInGame, g_tPlayer[0].tPosition.x, g_tPlayer[0].tPosition.y);

	for (int i = 0; i < g_iNumberPlayerInGame; i++)
	{
		//TGfxVec2 tMouvement = TGfxVec2(g_tPlayer[i].tPosition - g_tMousse.tMousse).Normalize() * g_tPlayer[i].fSpeed;
		//g_tPlayer[i].tPosition -= tMouvement;
		//if (g_tPlayer[i].tPosition != g_tMousse.tMousse)
		//{
		//	g_tPlayer[i].pSprite = DrawLine(g_tPlayer[i].pSprite, g_tPlayer[i].tPosition, g_tPlayer[i].fRatio);
		//}
		Controller(i);
	}

}
void Render()
{
	GfxClear(EGfxColor_Black);
	for (int i = 0; i < g_iNumberPlayerInGame; i++)
	{
	GfxSpriteRender(g_tPlayer[i].pSprite);
	}
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
	//GfxDefaultResolution(1280, 1024);
}
