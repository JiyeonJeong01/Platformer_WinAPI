#include "pch.h"
#include "CUIManager.h"
#include "CObject.h"
#include "CStageManager.h"

CUIManager* CUIManager::m_pInstance = nullptr;

CUIManager::CUIManager()
{

}

CUIManager::~CUIManager()
{
	Release();
}

void CUIManager::Initialize()
{

}

void CUIManager::Update()
{

}

void CUIManager::Render(HDC hDC)
{
	Render_Stage(hDC);

	
}

void CUIManager::Release()
{

}

void CUIManager::Render_Stage(HDC hDC)
{
	int stageNumber = CStageManager::Get_Instance()->Get_StageNumber();
	CUtility::PrintText(hDC, (WINCX >> 1) - 50, 50, L"Stage : ", stageNumber);
}

void CUIManager::Render_PlayerHP(HDC hDC, CObject* pObj)
{
    if (pObj == nullptr)
        return;

	CUtility::PrintText(hDC, 50, 100, L"플레이어 Hp : ", pObj->Get_HP());
    CUtility::PrintText(hDC, 50, 130, L"플레이어 공격력 : ", pObj->Get_Damage());
	DrawHP(hDC, 50, 50, 400, 40, pObj->Get_HP(), pObj->Get_MaxHP());
}

void CUIManager::Render_BossHP(HDC hDC, CObject* pObj)
{
    if (pObj == nullptr)
        return;

	CUtility::PrintText(hDC, (WINCX - 200), 100, L"보스 Hp : ", pObj->Get_HP());
	DrawHP(hDC, (WINCX - 450), 50, 400, 40, pObj->Get_HP(), pObj->Get_MaxHP(), HP_DIR::RightToLeft);
}

void CUIManager::DrawHP(HDC hDC, float x, float y, float width, float height, float Hp, float MaxHp, HP_DIR dir)
{
    Rectangle(hDC, (int)x - 1.0f, (int)(y - 1.0f), (int)(x + width + 1.0f), (int)(y + height + 1.2f));

    // Brush 빨간색으로 세팅
    HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 0));
    HPEN newPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

    HBRUSH prevBrush = (HBRUSH)SelectObject(hDC, newBrush);
    HPEN prevPen = (HPEN)SelectObject(hDC, newPen);

    float value = width * Hp / MaxHp;
    int left = 0, right = 0;

    // 왼쪽 기준
    if (dir == HP_DIR::LeftToRight)
    {
        left =  (int)x;
        right = (int)(x + value);
    }
    // 오른쪽 기준
    else 
    {
        left =  (int)(x + (width - value));
        right = (int)(x + width);
    }

    Rectangle(hDC, left, (int)y, right, (int)(y + height));

    // 사용한 Brush 삭제하고 원래대로 돌리기
    SelectObject(hDC, prevBrush);
    SelectObject(hDC, prevPen);
    DeleteObject(newBrush);
    DeleteObject(newPen);
}

void CUIManager::Render_GameClear(HDC hDC)
{
    Rectangle(hDC, 0, 0, WINCX, WINCY);

    HFONT hFont = CreateFont(80, 0, 0, 0, FW_BOLD,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        VARIABLE_PITCH, L"Segoe UI");
    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

    SetBkMode(hDC, TRANSPARENT);

    TCHAR buffer[64] = L"🏆  G A M E   C L E A R  🏆";

    RECT rc;
    GetClientRect(g_hWnd, &rc);

    SetTextColor(hDC, RGB(50, 50, 50));
    RECT shadow = rc;
    OffsetRect(&shadow, 5, 5);
    DrawText(hDC, buffer, lstrlen(buffer), &shadow,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SetTextColor(hDC, RGB(255, 215, 0));
    DrawText(hDC, buffer, lstrlen(buffer), &rc,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SelectObject(hDC, hOldFont);
    DeleteObject(hFont);


}
