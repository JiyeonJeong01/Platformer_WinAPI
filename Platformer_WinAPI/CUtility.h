#pragma once

#include "pch.h"

class CUtility
{
public:
    static void PrintText(HDC hdc, int x, int y, const wchar_t* buff, int value)
    {
        TCHAR buffer[64] = L"";
        swprintf_s(buffer, L"%s %d", buff, value);
        TextOut(hdc, x, y, buffer, lstrlen(buffer));
    }

    static void PrintText(HDC hdc, int x, int y, const wchar_t* label, float value)
    {
        TCHAR buffer[64] = L"";
        swprintf_s(buffer, L"%s %.2f", label, value);
        TextOut(hdc, x, y, buffer, lstrlen(buffer));
    }

};

