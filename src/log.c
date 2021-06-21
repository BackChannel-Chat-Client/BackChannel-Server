#include "log.h"

BC_STATUS
Bc_Platform_AppendToFile(const char* filename, const char* data)
{
	if (!filename || !data)
		return BC_INVALID_PARAM;

#ifdef _WIN32
	HANDLE hFile = NULL;
	int iResult = 0;
	DWORD dwMoved = 0;
	DWORD dwBytesWritten = 0;
	
	/*
		Open/create the file for appending
	*/
	hFile = CreateFileA(
		filename,				/* lpFileName */
		FILE_APPEND_DATA,		/* dwDesiredAccess */
		FILE_SHARE_READ,		/* dwShareMode */
		NULL,					/* lpSecurityAttributes */
		CREATE_NEW,				/* dwCreationDisposition*/
		FILE_ATTRIBUTE_NORMAL,	/* dwFlagsAndAttributes */
		NULL					/* hTemplateFile */
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "bad %lu\n", GetLastError());
		return BC_FILESYSTEM_ERROR;
	}

	/*
		Set file pointer to the end of the file
	*/
	dwMoved = SetFilePointer(
		hFile, 
		0l, 
		NULL, 
		FILE_END
	);
	if (dwMoved == INVALID_SET_FILE_POINTER)
	{
		CloseHandle(hFile);
		return BC_FILESYSTEM_ERROR;
	}

	/*
		Append data to file
	*/
	iResult = WriteFile(
		hFile, 
		data, 
		(DWORD)strlen(data), 
		&dwBytesWritten, 
		NULL
	);
	if (iResult == FALSE)
	{
		CloseHandle(hFile);
		return BC_FILESYSTEM_ERROR;
	}

	CloseHandle(hFile);
	return BC_SUCCESS;
#else
	return BC_UNIMPLEMENTED;
#endif
}

void
BcLogEx(const char* log)
{
#ifdef _DEBUG
	puts(log);
#else
	/*
		TODO: Implement logging to files
	*/
	puts(log);
	//Bc_Platform_AppendToFile("log.txt", log);
#endif
}

void 
BcErrorEx(FILE* output_stream, const char* lpError, const char* file, unsigned long line)
{
#ifdef _DEBUG
	fprintf(output_stream, "[-] ERROR %s %lu: %s\n", file, line, lpError);
#else
	/*
		TODO: Impelment logging to files
	*/
	fprintf(output_stream, "[-] ERROR %s %lu: %s", file, line, lpError);
#endif
}

void 
BcFatalErrorEx(FILE* output_stream, const char* lpError, const char* file, unsigned long line)
{
#ifdef _DEBUG
	fprintf(output_stream, "[-] FATAL ERROR %s %lu: %s\n", file, line, lpError);
#else
	/*
		TODO: Impelment logging to files
	*/
	fprintf(output_stream, "[-] FATAL ERROR %s %lu: %s", file, line, lpError);
#endif
	exit(-1);
}