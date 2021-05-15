#include "error.h"

void BcErrorEx(const char* lpError, const char* file, unsigned long line)
{
#ifdef _DEBUG
	fprintf(stderr, "[-] ERROR %s %d: %s\n", file, line, lpError);
#else
	/*
		TODO: Impelment logging to files
	*/
	fprintf(stderr, "[-] ERROR %s %d: %s", file, line, lpError);
#endif
}

void BcFatalErrorEx(const char* lpError, const char* file, unsigned long line)
{
#ifdef _DEBUG
	fprintf(stderr, "[-] FATAL ERROR %s %d: %s\n", file, line, lpError);
#else
	/*
		TODO: Impelment logging to files
	*/
	fprintf(stderr, "[-] FATAL ERROR %s %d: %s", file, line, lpError);
#endif
	exit(-1);
}