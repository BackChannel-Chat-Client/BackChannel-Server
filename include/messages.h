#pragma once

#include <stdint.h>

#include "common.h"

#include "channels.h"
#include "context.h"

typedef struct BC_MESSAGE
{
	uint32_t user;
	uint32_t time_sent;
	uint32_t id;
	uint32_t size;
	char* body;
} BC_MESSAGE, *P_BC_MESSAGE;