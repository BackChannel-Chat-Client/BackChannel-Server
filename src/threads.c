#include "threads.h"

BC_STATUS
Bc_Platform_StartThread(BC_THREAD_PROC thread_proc, void* parameter, BC_THREAD* thread_id)
{
	BC_THREAD thread_handle = NULL;

	if (!thread_proc || !thread_id)
		return BC_INVALID_PARAM;

#ifdef _WIN32
    thread_handle = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)thread_proc,
		parameter,
		0,
		NULL);
	if (!thread_handle)
		BcFatalError("Failed to create connection thread");

	*thread_id = thread_handle;

#else
    int result = pthread_create(
            &thread_handle,
            NULL,
            thread_proc,
            parameter);
    if (result)
        BcFatalError("Failed to create connection thread");

    *thread_id = thread_handle;
#endif

	return BC_SUCCESS;
}
