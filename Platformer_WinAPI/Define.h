#pragma once

#define	WINCX			1280
#define	WINCY			720

#define PURE			= 0

#define OBJ_DEAD		1
#define OBJ_NOEVENT		0

#define	PI				3.14f

/////////////////////////////////

extern HWND g_hWnd;

/////////////////////////////////

enum OBJID
{
	PLATFORM,
	PLAYER,
	PL_BULLET,
	MONSTER,
	MON_BULLET,
	MOUSE,
	SHIELD,
	ITEM,
	OBJ_END
};

enum STAGEID
{
	STAGE1 = 0,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE_END
};

/////////////////////////////////

template<typename T>
void	Safe_Delete(T& P) { if (P) { delete P; P = nullptr; } }

struct DeleteObj
{
	template<typename T>
	void	operator()(T& p) { if (p) { delete p; p = nullptr; } }
};

/////////////////////////////////

#include "Vector2.h"

typedef struct tagLine
{
	Vector2 tLeft;
	Vector2 tRight;

	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}

	tagLine(Vector2 _tLeft, Vector2 _tRight)
		: tLeft(_tLeft), tRight(_tRight)
	{
	}
}
LINE;

struct DeleteMap
{
	template<typename T>
	void	operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};

struct tagFinder
{
	tagFinder(const TCHAR* pTag) : m_pTag(pTag)
	{
	}

	template<typename T>
	bool operator()(T& MyPair)
	{
		return !lstrcmp(MyPair.first, m_pTag);
	}


	const TCHAR* m_pTag;
};

