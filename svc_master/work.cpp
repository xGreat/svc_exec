#include <windows.h>
#include <tchar.h>
#include <wtsapi32.h>
#include <userenv.h>
#include "log.h"

#pragma comment(lib, "wtsapi32")
#pragma comment(lib, "userenv")

VOID SvcWork()
{
    DWORD dwSessionId = WTSGetActiveConsoleSessionId();

    HANDLE hToken = NULL;
#ifndef USE_LOCAL_SYSTEM_ACCOUNT
    WTSQueryUserToken(dwSessionId, &hToken);
#else
    OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &hToken);
#endif

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.lpDesktop = TEXT("winsta0\\default");

    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    PVOID lpEnvironment = NULL;
    CreateEnvironmentBlock(&lpEnvironment, hToken, FALSE);

    LPTSTR szCmdline = _tcsdup(_T("\"svc_worker.exe\""));

    CreateProcessAsUser(hToken,
        NULL,
        szCmdline,
        NULL,
        NULL,
        FALSE,
        NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
        lpEnvironment,
        NULL,
        &si,
        &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    CloseHandle(hToken);
}