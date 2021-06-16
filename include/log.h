#pragma once

#ifdef _WIN32
	#include <WinSock2.h>
#else
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"

#define BcLog( log ) (BcLogEx(log))
#define BcError( lpError ) (BcErrorEx(stderr, lpError, __FILE__, __LINE__))
#define BcFatalError( lpError ) (BcFatalErrorEx(stderr, lpError, __FILE__, __LINE__))

void
BcLogEx(const char* log);

/*
	Prints out an error to the stderr stream

	TODO: Add logging
*/
void
BcErrorEx(FILE* output_stream, const char* lpError, const char* file, unsigned long line);

/*
	Prints out an error to the stderr stream, and exits the program with code
	of -1.

	TODO: Add logging
*/
void
BcFatalErrorEx(FILE* output_stream, const char* lpError, const char* file, unsigned long line);