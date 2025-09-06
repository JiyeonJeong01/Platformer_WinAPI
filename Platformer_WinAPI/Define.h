#pragma once

#define	WINCX		800
#define	WINCY		600

#define PURE	= 0

#define OBJ_DEAD		1
#define OBJ_NOEVENT		0

#define	PI		3.14f

extern HWND g_hWnd;

enum OBJID { PLAYER, BULLET, MONSTER, MOUSE, SHIELD, ITEM, OBJ_END };

enum STAGEID { STAGE1 = 0, STAGE2, STAGE3, STAGE4, STAGE_END };

template<typename T>
void	Safe_Delete(T& P) { if (P) { delete P; P = nullptr; }}

struct DeleteObj
{
	template<typename T>
	void	operator()(T& p) { if (p) { delete p; p = nullptr; } }
};

// For testing in Stage04. Can be modified or deleted freely.
typedef struct tagLinePoint
{
	float fPosX, fPosY;

	tagLinePoint()
	{
		ZeroMemory(this, sizeof(tagLinePoint));
	}

	tagLinePoint(float _fX, float _fY)
		: fPosX(_fX), fPosY(_fY) {
	}
}
LINEPOINT;

typedef struct tagLine
{
	LINEPOINT tLeft;
	LINEPOINT tRight;

	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}

	tagLine(LINEPOINT _tLeft, LINEPOINT _tRight)
		: tLeft(_tLeft), tRight(_tRight) {
	}
}
LINE;