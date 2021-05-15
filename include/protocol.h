#pragma once

#include <stdint.h>

#include "main.h"
#include "networking.h"

typedef struct BC_PACKET
{
	uint32_t	packet_size;
	uint32_t	packet_id;
	uint32_t	channel_id;
	uint8_t		req_type;
	char*		auth_key;
	char*		req_body;
} BC_PACKET, *P_BC_PACKET;

BC_STATUS
BcParseRequest(char* buffer, size_t buffer_size, P_BC_PACKET packet);