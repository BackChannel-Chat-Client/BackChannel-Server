#include "networking.h"

void
BcConnectionHandler(void* parameter)
{
	BC_STATUS bcResult = 0;
	char recv_buffer[4096] = { 0 };
	int bytes_received = 0;
	P_BC_CONNECTION bcConnection = NULL;
	BC_REQ_PACKET bcPacket = { 0 };
	
	bcConnection = (P_BC_CONNECTION)parameter;
	if (!bcConnection)
	{
		BcError("BcConnectionHandler received a null connection pointer");
		return;
	}

	BcLog("[+] Got new connection");

	while ((bytes_received = recv(bcConnection->sock, recv_buffer, sizeof(recv_buffer), 0)) > 0)
	{
		/*
			NULL-Terminate the buffer. If recv receives 4096 bytes, it is not guaranteed
			that the final byte is the null byte of the req_body member.
		*/
		recv_buffer[4095] = 0;

		bcResult = BcParseRequest(recv_buffer, bytes_received, &bcPacket);
		if (bcResult != BC_SUCCESS)
		{
			BcError("Failed to parse request");
			continue;
		}

		printf("packet_size: %d\npacket_id: %d\nchannel_id: %d\nreq_type: 0x%x\nauth_key: %s\nreq_body: %s\n", 
					bcPacket.packet_size,
					bcPacket.packet_id,
					bcPacket.channel_id,
					bcPacket.req_type,
					bcPacket.auth_key,
					bcPacket.req_body);

		BcHandleRequest(bcConnection, &bcPacket);

		free(bcPacket.auth_key);
		free(bcPacket.req_body);
	}

	closesocket(bcConnection->sock);
	free(bcConnection);
}

BC_STATUS
BcNetSendUint32(P_BC_CONNECTION conn, uint32_t status)
{
	if (!conn)
		return BC_INVALID_PARAM;

	if (!conn->sock)
		return BC_NOT_CONNECTED;

	// TODO: This isn't insecure, right?
	if (send(conn->sock, (char*)&status, sizeof(status), 0) < 0)
	{
		BcError("Couldn't send data to client... closing socket.");

		return BC_NETWORK_ERROR;
	}

	return BC_SUCCESS;
}

BC_STATUS
BcInitializeNet(void)
{
#ifdef _WIN32
	WORD wVersionRequested = 0;
	WSADATA wsaData = { 0 };
	int iResult = 0;

	wVersionRequested = MAKEWORD(2, 2);

	iResult = WSAStartup(wVersionRequested, &wsaData);
	if (iResult != 0) 
		return BC_NETWORK_ERROR;
#endif

	return BC_SUCCESS;
}

BC_STATUS
BcHandleNewConnections(P_BC_CONTEXT bc_context, unsigned short port)
{
	BC_STATUS bcResult = 0;
	struct sockaddr_in lpServerInfo = { 0 };
	struct sockaddr lpClientInfo = { 0 };
	int sockaddr_in_size = sizeof(struct sockaddr_in);
	SOCKET serverSock = 0;
	SOCKET clientSock = 0;
	P_BC_CONNECTION bcConnection = NULL;
	HANDLE thread_handle = NULL;

	if (!bc_context)
		return BC_INVALID_PARAM;

	/*
		Create the server socket
	*/
	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock == INVALID_SOCKET)
		BcFatalError("Could not create socket");

	/*
		Prepare the sockaddr_in structure
	*/
	lpServerInfo.sin_family = AF_INET;
	lpServerInfo.sin_addr.s_addr = INADDR_ANY;
	lpServerInfo.sin_port = htons(port);

	/*
		Bind the server to the specified port
	*/
	if (bind(serverSock, (struct sockaddr*)&lpServerInfo, sizeof(lpServerInfo)) < 0)
		BcFatalError("Could not bind to port");

	/*
		Begin listening for new connections
	*/
	listen(serverSock, SOMAXCONN);

	BcLog("[+] Waiting for incoming connections...");

	/*
		Accept many connections infinitely
	*/
	do
	{
		/*
			Accept new connection
			TODO: Add a POSIX form of INVALID_SOCKET to the defines
		*/
		clientSock = accept(serverSock, &lpClientInfo, &sockaddr_in_size);
		if (clientSock == INVALID_SOCKET)
		{
			BcError("Failed to accept connection");
			
			continue;
		}

		BcLog("[+] Connection accepted");

		/*
			Allocate new BC_CONNECTION struct
		*/
		bcConnection = malloc(sizeof(BC_CONNECTION));
		if (!bcConnection)
		{
			BcError("Failed to allocate connection struct");
			closesocket(clientSock);
			
			continue;
		}

		/*
			Set struct members
		*/
		bcConnection->sock = clientSock;
		bcConnection->connInfo = lpClientInfo;
		bcConnection->bc_context = bc_context;
		bcConnection->bc_errno = BC_SUCCESS;

		/*
			Start a new thread to handle connection
		*/
		bcResult = Bc_Platform_StartThread(BcConnectionHandler, bcConnection, &thread_handle);
		if (bcResult != BC_SUCCESS)
		{
			BcError("Failed to start connection thread");
			closesocket(bcConnection->sock);
			free(bcConnection);

			continue;
		}
	} while (1);

	return BC_SUCCESS;
}