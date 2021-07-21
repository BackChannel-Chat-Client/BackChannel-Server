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

	/*
		Assign members
	*/
	(*channel)->channel_name = channel_name;
	(*channel)->channel_id = context->channel_count;
	(*channel)->max_messages = max_messages;
	
	/*
		TODO: Implement messages
	*/
	(*channel)->message_list = malloc(sizeof(*(*channel)->message_list) * (*channel)->max_messages);
	if (!(*channel)->message_list)
		BcFatalError("Failed to allocate memory");

	memset((*channel)->message_list, 0, sizeof(*(*channel)->message_list) * (*channel)->max_messages);

	(*channel)->message_count = 0;

	return BC_SUCCESS;
}

