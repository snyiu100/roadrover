#pragma once
#include <windows.h>


class Logger
{
public:
	Logger();
	~Logger();

	bool init();
	void close();
	void write(LPCSTR filename, LPCSTR func);
	void write(LPCSTR filename, LPCSTR func, LPVOID data, DWORD size);

private:
	FILE* file;
};

extern Logger logger;
