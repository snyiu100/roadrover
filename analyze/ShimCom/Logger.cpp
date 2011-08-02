#include "Logger.h"


#ifndef min
#	define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif


Logger logger;


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
	close();
	file = fopen("\\com_log.txt", "a");
	if(file)
	{
		fprintf(file, "\n--- Start ---\n");
		return true;
	}
	return false;
}

void Logger::close()
{
	if(file) {
		fprintf(file, "\n--- End ---\n");
		fclose(file);
		file = NULL;
	}
}

void Logger::write(LPCSTR filename, LPCSTR func)
{
	if(file) {
		fprintf(file, "\n%s (%s)\n", func, filename);
	}
}

void Logger::write(LPCSTR filename, LPCSTR func, LPVOID data, DWORD size)
{
    if(file && size)
	{
		fprintf(file, "\n%s (%s) size=%i\n", func, filename, size);
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
	}
}
