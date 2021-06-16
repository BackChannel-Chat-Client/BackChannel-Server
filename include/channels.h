#pragma once

#include <stdint.h>

#include "common.h"
#include "context.h"

/*
	Why can't I be happy
*/
typedef struct _BC_CONTEXT *P_BC_CONTEXT;

typedef struct _BC_CHANNEL
{
	uint32_t channel_id;
	uint32_t max_messages;
	/*TODO: Message head*/ void* message_head;
	char* channel_name;
} BC_CHANNEL, *P_BC_CHANNEL;

BC_STATUS BcChanRegisterChannel(P_BC_CONTEXT bc_context, char* channel_name, uint32_t max_messages, P_BC_CHANNEL *channel);
