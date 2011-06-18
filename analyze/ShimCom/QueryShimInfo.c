#include <windows.h>
#include "QueryShimInfo.h"
#include "ShimInfo.h"

extern HINSTANCE g_hinstDll;

#define MAX_STRING_LEN 4096

//
// QueryShimInfo:
//
// AppVerif.exe will call into this function to get information about the shim
// to display in the UI. The Application Verifier engine will use the presence
// of this exported function to determine whether a loaded dll is a shim dll.
// Therefore, this function must be exported by every shim dll.
//

BOOL QueryShimInfo (int nReason, LPWSTR *ppszString)
// [in] nReason - the string needed. Will be one of the QUERYSHIMINFO_* values.
// [out] ppszString - pointer to a string pointer. The memory must be allocated
//                  using LocalAlloc. The app verifier UI will free the memory.
{
    BOOL fRet = TRUE;

    switch (nReason)
    {
        case QUERYSHIMINFO_DESCRIPTION: // Description
        {
            // The shim dll is responsible for allocating a buffer containing
            // a description, using LocalAlloc. AppVerif.exe will free the buffer.

            // This description will be used in appverif.exe's description pane
            // when the shim is selected.
            *ppszString = LocalAlloc (LMEM_ZEROINIT, MAX_STRING_LEN * sizeof (TCHAR));
            if (*ppszString)
            {
                LoadString(g_hinstDll,
                    AVS_GENERATED_DESC,
                    *ppszString,
                    MAX_STRING_LEN
                    );
            }
            break;
        }

        case QUERYSHIMINFO_FRIENDLYNAME: // Friendly name
        {
            // The shim dll is responsible for allocating a buffer containing
            // a friendly name, using LocalAlloc. AppVerif.exe will free the buffer.

            // This friendly name will be used in appverif.exe's panel
            // containing the list of available shims.
            *ppszString = LocalAlloc (LMEM_ZEROINIT, MAX_STRING_LEN * sizeof (TCHAR));
            if (*ppszString)
            {
                LoadString(g_hinstDll,
                    AVS_GENERATED_FRIENDLY,
                    *ppszString,
                    MAX_STRING_LEN
                    );
            }
            break;
        }

        default:
        {
            // Ignore all other requests.
            fRet = FALSE;
            break;
        }
    }

    return fRet;
}

