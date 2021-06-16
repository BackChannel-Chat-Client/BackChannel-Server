#include "context.h"

BC_STATUS BcCtxInit(P_BC_CONTEXT *bc_context, uint32_t max_channels)
{
	P_BC_CONTEXT context = NULL;

	/*
		If context contains a valid address, 
		we don't want to cause a dangling ptr or some shit
	*/
	if (!bc_context || max_channels == 0)
		return BC_INVALID_PARAM;

	context = malloc(sizeof(*context));
	if (context == NULL)
		BcFatalError("Failed to allocate memory");

	context->channel_list = malloc(sizeof(*(context->channel_list)) * max_channels);
	if (context->channel_list == NULL)
		BcFatalError("Failed to allocate memory");

	context->channel_count = 0;
	context->max_channel_count = max_channels;

	/*
		We set all of the channels to NULL so we can check if a channel is set
	*/
	for (uint32_t i = 0; i < context->max_channel_count; i++)
	{
		context->channel_list[i].channel_id = 0;
		context->channel_list[i].channel_name = NULL;
		context->channel_list[i].max_messages = 0;
		context->channel_list[i].message_head = NULL;
	}

	*bc_context = context;

	return BC_SUCCESS;
}