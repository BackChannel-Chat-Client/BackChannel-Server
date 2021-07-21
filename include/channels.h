#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "common.h"
#include "context.h"
#include "messages.h"

/*
	Why can't I be happy
*/
typedef struct _BC_CONTEXT *P_BC_CONTEXT;

typedef struct _BC_CHANNEL
{
	uint32_t channel_id;
	uint32_t max_messages;
	/*TODO: Message head*/ P_BC_MESSAGE message_list;
	uint32_t message_count;
	char* channel_name;
} BC_CHANNEL, *P_BC_CHANNEL;

BC_STATUS BcChanRegisterChannel(P_BC_CONTEXT bc_context, char* channel_name, uint32_t max_messages, P_BC_CHANNEL *channel);
