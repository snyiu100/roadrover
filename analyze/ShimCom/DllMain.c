#include <windows.h>

#ifdef UNDER_NT
#include <tchar.h>
#define NKDbgPrintfW _tprintf
#endif

// ----------------------------------------------------------------------------
// Global variables

HINSTANCE g_hinstDll = NULL;

// ----------------------------------------------------------------------------
// DllMain

BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpVoid)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        NKDbgPrintfW (_T("%s: DLL_PROCESS_ATTACH\r\n"), _T(__FILE__));
        g_hinstDll = hInstance;
        break;
    case DLL_PROCESS_DETACH:
        NKDbgPrintfW (_T("%s: DLL_PROCESS_DETACH\r\n"), _T(__FILE__));
        break;
    case DLL_THREAD_ATTACH:
        NKDbgPrintfW (_T("%s: DLL_THREAD_ATTACH\r\n"), _T(__FILE__));
        break;
    case DLL_THREAD_DETACH:
        NKDbgPrintfW (_T("%s: DLL_THREAD_DETACH\r\n"), _T(__FILE__));
        break;
    default:
        NKDbgPrintfW (_T("%s: ERROR!!! Unknown dwReason: %d\r\n"), _T(__FILE__), dwReason);
        return FALSE;
        break;
    }

    return TRUE;
}

