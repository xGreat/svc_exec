#pragma once
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdarg.h>

void DbgPrintf(LPCTSTR lpszFormat, ...);