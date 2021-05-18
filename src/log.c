#include "log.h"

void
BcLog(const char* log)
{
#ifdef _DEBUG
	puts(log);
#else
	/*
		TODO: Implement logging to files
	*/
	puts(log);
#endif
}

void BcErrorEx(const char* lpError, const char* file, unsigned long line)
{
#ifdef _DEBUG
	fprintf(stderr, "[-] ERROR %s %lu: %s\n", file, line, lpError);
#else
	/*
		TODO: Impelment logging to files
	*/
	fprintf(stderr, "[-] ERROR %s %lu: %s", file, line, lpError);
#endif
}

void BcFatalErrorEx(const char* lpError, const char* file, unsigned long line)
{
#ifdef _DEBUG
	fprintf(stderr, "[-] FATAL ERROR %s %lu: %s\n", file, line, lpError);
#else
	/*
		TODO: Impelment logging to files
	*/
	fprintf(stderr, "[-] FATAL ERROR %s %lu: %s", file, line, lpError);
#endif
	exit(-1);
}