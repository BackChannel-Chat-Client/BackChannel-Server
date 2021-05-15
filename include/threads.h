#pragma once

#ifdef _WIN32
	#include <WinSock2.h>
	typedef void(WINAPI* BC_THREAD_PROC)(LPVOID lpParameter);
#else
	#include <pthread.h>
	typedef void(* BC_THREAD_PROC)(void* lpParameter);
#endif

#include "main.h"

typedef void* BC_THREAD;

BC_STATUS
Bc_Platform_StartThread(BC_THREAD_PROC thread_proc, void* parameter, BC_THREAD* thread_id);