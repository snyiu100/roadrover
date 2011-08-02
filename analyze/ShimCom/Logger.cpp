#include "Logger.h"


#ifndef min
#	define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif


Logger logger;
const char* filename = "\\com_log.txt";


Logger::Logger()
: file(NULL)
{
	init();
}

Logger::~Logger()
{
	close();
}

bool Logger::init()
{
	return true;
}

void Logger::close()
{
}

void Logger::write(LPCSTR filename, LPCSTR func)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	FILE* file = fopen(filename, "a");
	fprintf(file, "\n%d:%d.%d\t%s (%s)\n", st.wMinute, st.wSecond, st.wMilliseconds, func, filename);
	fclose(file);
}

void Logger::write(LPCSTR filename, LPCSTR func, LPVOID data, DWORD size)
{
    if(size)
	{
		SYSTEMTIME st;
		GetSystemTime(&st);
		FILE* file = fopen(filename, "a");
		fprintf(file, "\n%d:%d.%d\t%s (%s) size=%i\n", st.wMinute, st.wSecond, st.wMilliseconds, func, filename, size);
		for(DWORD i=0; i<size;)
		{
			char hex[49];
			char str[17];
			DWORD len = min(size - i, 16);
			for(DWORD j=0; j<len; ++j, ++i)
			{
				BYTE ch = ((LPBYTE)data)[i];
				sprintf(&hex[j*3], "%.2X ", ch);
				str[j] = ch > 0x20 && ch < 0x80 ? ch : '.';
			}
			str[len] = '\0';
			fprintf(file, "%-48s\t%s\n", hex, str);
		}
		fclose(file);
	}
}
