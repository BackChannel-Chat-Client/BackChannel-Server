#include "channels.h"

BC_STATUS BcChanRegisterChannel(P_BC_CONTEXT context, char* channel_name, uint32_t max_messages, P_BC_CHANNEL *channel)
{
	BC_UNREFERENCED_PARAMETER(max_messages);
	
	if (!context || !channel_name || !channel)
		return BC_INVALID_PARAM;

	if (!context->channel_list)
		return BC_INVALID_CONTEXT;

	if (context->channel_count >= context->max_channel_count)
		return BC_CHANNEL_LIMIT_HIT;

	/*
		What the fuck
	*/
	if ((*channel = &context->channel_list[context->channel_count++]) == NULL)
	{
		/* Decrement channel count because yeah */
		--context->channel_count; 

		return BC_INVALID_CONTEXT;
	}

	(*channel)->channel_name = channel_name;
	(*channel)->channel_id = context->channel_count;
	(*channel)->max_messages = max_messages;
	
	/*
		TODO: Implement messages
	*/
	// (*channel)->message_head = malloc(sizeof(*(channel->message_head)) * channel->max_messages);

	return BC_SUCCESS;
}

