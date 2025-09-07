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

    static void PrintCmd(const wchar_t* text, int value)
    {
        wprintf(L"%s %d\n", text, value);
    }

    static void PrintCmd(const wchar_t* text, float value)
    {
        wprintf(L"%s %.2f\n", text, value);
    }
};

