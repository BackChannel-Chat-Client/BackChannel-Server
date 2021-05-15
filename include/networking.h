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

#include "main.h"
#include "log.h"
#include "error.h"
#include "threads.h"
#include "protocol.h"

typedef struct BC_CONNECTION
{
	SOCKET sock;
	struct sockaddr_in connInfo;
} BC_CONNECTION, *P_BC_CONNECTION;

BC_STATUS
BcInitializeNet(void);

BC_STATUS
BcHandleNewConnections(unsigned short port);