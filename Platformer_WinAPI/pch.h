#ifndef PCH_H
#define PCH_H

#include "framework.h"

#include <cmath>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <Windows.h>

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#endif
#endif

using namespace std;

#include "Define.h"
#include "Vector2.h"
#include "CUtility.h"

#include "CCollisionManager.h"
#include "CInputManager.h"
#include "CScrollManager.h"
#include "CLineManager.h"
#include "CObjectManager.h"
#include "CStageManager.h"
#include "CUIManager.h"

#endif //PCH_H
