#pragma once

#include "pch.h"

class CUtility
{
public:
    static void PrintText(HDC hdc, int x, int y, const wchar_t* text, int value)
    {
        TCHAR buffer[64] = L"";
        swprintf_s(buffer, L"%s %d", text, value);
        TextOut(hdc, x, y, buffer, lstrlen(buffer));
    }

    static void PrintText(HDC hdc, int x, int y, const wchar_t* text, float value)
    {
        TCHAR buffer[64] = L"";
        swprintf_s(buffer, L"%s %.2f", text, value);
        TextOut(hdc, x, y, buffer, lstrlen(buffer));
    }

    static void PrintText(HDC hdc, int x, int y, const wchar_t* text, float value1, float value2)
    {
        TCHAR buffer[64] = L"";
        swprintf_s(buffer, L"%s %.2f / %.2f", text, value1, value2);
        TextOut(hdc, x, y, buffer, lstrlen(buffer));
    }
    //CUtility::PrintText(hdc, 좌표 x,y , 텍스트, 출력 값)

    static void PrintCmd(const wchar_t* text, int value)
    {
        wprintf(L"%s %d\n", text, value);
    }

    static void PrintCmd(const wchar_t* text, float value)
    {
        wprintf(L"%s %.2f\n", text, value);
    }

    static void PrintCmd(const wchar_t* text, Vector2 value)
    {
        wprintf(L"%s %.2f %.2f\n", text, value.x, value.y);
    }
    //CUtility::PrintCmd(L"가나다 : ", 출력하고 싶은 값); <<- 이렇게 사용하세요
};

