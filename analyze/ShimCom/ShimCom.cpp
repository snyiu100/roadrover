#include <windows.h>
#include <map>
#include <atlbase.h>
#include <atlstr.h>
#include "Logger.h"

#ifdef UNDER_NT
#	include <tchar.h>
#endif


typedef std::map<HANDLE, CStringA> Files;
Files files;


HANDLE __stdcall APIHook_CreateFileW( 
    LPWSTR lpFileName,
    unsigned long int dwDesiredAccess,
    unsigned long int dwShareMode,
    LPSECURITY_ATTRIBUTES lpsa,
    unsigned long int dwCreationDisposition,
    unsigned long int dwFlagsAndAttributes,
    LPVOID hTemplateFile)
{
    HANDLE hFile = CreateFileW (
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpsa,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile);

	if(hFile != INVALID_HANDLE_VALUE && wcsstr(lpFileName, L"COM") == lpFileName)
	{
		files[hFile] = lpFileName;
		logger.write(files[hFile], "CreateFileW");
	}
    return hFile;
}


BOOL __stdcall APIHook_ReadFile( 
    LPVOID hFile,
    LPVOID lpBuffer,
    unsigned long int nNumberOfBytesToRead,
    unsigned long int * lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped)
{
    BOOL result = ReadFile (
        hFile,
        lpBuffer,
        nNumberOfBytesToRead,
        lpNumberOfBytesRead,
        lpOverlapped);

	Files::iterator it = files.find(hFile);
	if(result == TRUE && it != files.end())
	{
		logger.write(it->second, "ReadFile", lpBuffer, *lpNumberOfBytesRead);
	}
    return result;
}


BOOL __stdcall APIHook_WriteFile( 
    LPVOID hFile,
    LPVOID lpBuffer,
    unsigned long int nNumberOfBytesToWrite,
    unsigned long int * lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped)
{
    BOOL result = WriteFile (
        hFile,
        lpBuffer,
        nNumberOfBytesToWrite,
        lpNumberOfBytesWritten,
        lpOverlapped);

	Files::iterator it = files.find(hFile);
	if(it != files.end())
	{
		logger.write(it->second, result == TRUE ? "WriteFile""WriteFile OK" : "WriteFile ERROR", lpBuffer, nNumberOfBytesToWrite);
	}
    return result;
}
