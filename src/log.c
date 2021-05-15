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