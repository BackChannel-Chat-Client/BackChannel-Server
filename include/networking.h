#pragma once

#ifdef _WIN32
	#include <WinSock2.h>
	#pragma comment(lib, "ws2_32.lib")
#elif __unix__
	#include<sys/socket.h>
	#include<netdb.h>
	#include<arpa/inet.h>

	typedef int SOCKET;
#endif

#include <stdio.h>
#include <stdint.h>

#include "common.h"

#include "log.h"
#include "threads.h"
#include "protocol.h"

typedef struct _BC_CONNECTION
{
	SOCKET sock;
	struct sockaddr connInfo;
	uint32_t bc_errno;
} BC_CONNECTION, *P_BC_CONNECTION;

BC_STATUS
BcNetSendUint32(P_BC_CONNECTION conn, uint32_t status);

BC_STATUS
BcInitializeNet(void);

BC_STATUS
BcHandleNewConnections(unsigned short port);