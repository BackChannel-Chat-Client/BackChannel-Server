#include "channels.h"

BC_STATUS BcChanRegisterChannel(P_BC_CONTEXT context, char* channel_name, uint32_t max_messages, P_BC_CHANNEL *channel)
{
	uint32_t newChannelId = 0;

	BC_UNREFERENCED_PARAMETER(max_messages);
	
	if (!context || !channel_name || !channel)
		return BC_INVALID_PARAM;

	if (!context->channel_list)
		return BC_INVALID_CONTEXT;

	if (context->channel_count >= context->max_channel_count)
		return BC_CHANNEL_LIMIT_HIT;

	/* 
		Set channel id to the current channel count so we append
		to the end of the array (if we aren't slotting into an empty slot).
	*/
	newChannelId = context->channel_count;

	/*
		Walk the array of channels. If a previous channel has been deleted,
		we use that position/id for the new channel.
	*/
	for (uint32_t i = 0; i < context->channel_count; i++)
	{
		/* if id == 0 (uninitialized), we slot ourselves in there*/
		if (context->channel_list[i].channel_id == 0)
			newChannelId = i;
	}

	/*
		Get pointer to the empty channel slot at the specified ID
		What the fuck
	*/
	if ((*channel = &context->channel_list[newChannelId]) == NULL)
	{
		/* Decrement channel count because yeah */
		/*--context->channel_count;*/ 

		return BC_INVALID_CONTEXT;
	}

	/*
		Assign members to channel struct
	*/
	(*channel)->channel_name = channel_name;
	(*channel)->channel_id = context->channel_count;
	(*channel)->max_messages = max_messages;
	
	/*
		Increment channel count
	*/
	++(context->channel_count);

	/*
		TODO: Implement messages
	*/
	// (*channel)->message_head = malloc(sizeof(*(channel->message_head)) * channel->max_messages);

	return BC_SUCCESS;
}

