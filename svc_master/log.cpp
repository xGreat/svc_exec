#include "log.h"

void DbgPrintf(LPCTSTR lpszFormat, ...)
{
    TCHAR szBuffer[4096];

    va_list args;
    va_start(args, lpszFormat);
    _vstprintf(szBuffer, lpszFormat, args);
    va_end(args);

    OutputDebugString(szBuffer);
}