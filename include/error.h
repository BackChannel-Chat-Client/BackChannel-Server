#pragma once

#include <stdio.h>

#define BcError( lpError ) (BcErrorEx(lpError, __FILE__, __LINE__))
#define BcFatalError( lpError ) (BcFatalErrorEx(lpError, __FILE__, __LINE__))

/*
	Prints out an error to the stderr stream

	TODO: Add logging
*/
void BcErrorEx(const char* lpError, const char* file, unsigned long line);

/*
	Prints out an error to the stderr stream, and exits the program with code
	of -1.

	TODO: Add logging
*/
void BcFatalErrorEx(const char* lpError, const char* file, unsigned long line);