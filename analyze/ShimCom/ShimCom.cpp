#include <windows.h>
#include <map>
#include <atlbase.h>
#include <atlstr.h>

#ifdef UNDER_NT
#	include <tchar.h>
#endif

#ifndef min
#	define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif


void LogToFile(LPCSTR filename, LPCSTR func, LPVOID data=NULL, DWORD size=0)
{
	if(data && size)
	{
		FILE* file = fopen ("\\com_log.txt", "ab");
		fprintf(file, "\n%s (%s) size=%i\n", func, filename, size);
		for(DWORD i=0; i<size;)
		{
			char hex[49];
			char str[17];
			DWORD len = min(size - i, 16);
			for(DWORD j=0; j<len; ++j, ++i)
			{
				char ch = ((LPBYTE)data)[i];
				sprintf(&hex[j*3], "%.2X ", ch);
				str[j] = ch > 0x20 && ch < 0x80 ? ch : '.';
			}
			str[len] = '\0';
			fprintf(file, "%-48s\t%s\n", hex, str);
		}
		fclose (file);
	}
}


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
		LogToFile(files[hFile], "CreateFileW");
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
		LogToFile(it->second, "ReadFile", lpBuffer, *lpNumberOfBytesRead);
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
		LogToFile(it->second, result == TRUE ? "WriteFile""WriteFile OK" : "WriteFile ERROR", lpBuffer, nNumberOfBytesToWrite);
	}

    return result;
}

