#pragma once

#include <stdlib.h>

#include "common.h"
#include "log.h"
#include "channels.h"

/*
	I hate you
*/
typedef struct _BC_CHANNEL* P_BC_CHANNEL;

typedef struct _BC_CONTEXT
{
	P_BC_CHANNEL	channel_list;
	uint32_t			channel_count;
	uint32_t			max_channel_count;
} BC_CONTEXT, * P_BC_CONTEXT;

BC_STATUS BcCtxInit(P_BC_CONTEXT* bc_context, uint32_t max_channels);