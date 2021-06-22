#pragma once

#ifdef _WIN32
	#include <WinSock2.h>
	#pragma comment(lib, "ws2_32.lib")

	/* I hate MSVC */
	#define strdup _strdup
#elif __unix__
	#include<sys/socket.h>
	#include<netdb.h>
	#include<arpa/inet.h>

	typedef int SOCKET;
#endif

#include <stdint.h>
#include <string.h>

#include "common.h"

#include "networking.h"
#include "log.h"
#include "tls.h"

/*
	Request includes	
*/
#include "requests/BACKCHANNEL_REQ_GET_ERRNO.h"
#include "requests/BACKCHANNEL_REQ_GET_CHANNELS.h"

/*
	Request types
*/
#define BACKCHANNEL_REQ_GET_ERRNO			0x00	/* Get last error												*/
#define BACKCHANNEL_REQ_AUTH				0x01	/* Verify authentication key									*/
#define BACKCHANNEL_REQ_REGISTER			0x02	/* Register for new authentication key							*/
#define BACKCHANNEL_REQ_VERIFY_SECURITY		0x03	/* Verify the integrity of communications (somehow)				*/
#define BACKCHANNEL_REQ_REGISTER_FOR_EVENT	0x04	/* Register connection to receive info on events. (i.e. new messages, new users, etc) */
#define BACKCHANNEL_REQ_GET_CHANNELS		0x10	/* Get a list of all channel ids accessible to your auth key	*/
#define BACKCHANNEL_REQ_SEND_MESSAGE		0x11	/* Send a message to the channel ID specified					*/
#define BACKCHANNEL_REQ_GET_MESSAGE			0x12	/* Get message by its ID										*/

/*
	Minimum packet size is 15 bytes
	13 bytes for the integral members, and 2 bytes for the null characters in the `auth_key` and `req_body` buffers.
*/
#define BC_MINIMUM_REQUEST_PACKET_SIZE 15 
#define BC_MINIMUM_RESPONSE_PACKET_SIZE 13

typedef struct _BC_REQ_PACKET
{
	uint32_t	packet_size;
	uint32_t	packet_id;
	uint32_t	channel_id;
	uint8_t		req_type;
	char*		auth_key;
	char*		req_body;
} BC_REQ_PACKET, *P_BC_REQ_PACKET;
//typedef BC_REQ_PACKET* P_BC_REQ_PACKET;

typedef struct _BC_RESP_PACKET
{
	uint32_t	packet_size;
	uint32_t	packet_id;
	uint32_t	resp_status;
	char* resp_body;
} BC_RESP_PACKET, * P_BC_RESP_PACKET;

/*
	Forward declaration of P_BC_CONNECTION.
	I hate compilers! I hate compilers!
*/
typedef struct _BC_CONNECTION *P_BC_CONNECTION;

BC_STATUS
BcParseRequest(char* buffer, size_t buffer_size, P_BC_REQ_PACKET packet);

BC_STATUS
BcVerifyRequestPacket(P_BC_REQ_PACKET packet);

BC_STATUS
BcHandleRequest(P_BC_CONNECTION conn, P_BC_REQ_PACKET packet);

BC_STATUS
BcSendResponse(P_BC_CONNECTION conn, uint32_t packet_id, uint32_t resp_status, char* resp_body, uint32_t resp_body_size);