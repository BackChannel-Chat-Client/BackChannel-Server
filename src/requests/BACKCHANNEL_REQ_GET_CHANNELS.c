#include "requests/BACKCHANNEL_REQ_GET_CHANNELS.h"

BC_STATUS
BcReqGetChannels(P_BC_CONNECTION conn, P_BC_REQ_PACKET packet)
{
	char* respBuffer = NULL;
	P_BC_CHANNEL tempChannel = NULL;
	uint32_t channelNameSize = 0;
	uint32_t respBufferSize = 0;
	
	if (!conn || !packet)
		return BC_INVALID_PARAM;

	if (!conn->sock)
		return BC_NOT_CONNECTED;

	if (!conn->bc_context)
		return BC_INVALID_CONTEXT;

	if (!conn->bc_context->channel_list)
		return BC_INVALID_CONTEXT;

	if (BcVerifyRequestPacket(packet) != BC_SUCCESS)
	{
		conn->bc_errno = BC_INVALID_PACKET;
		BcSendResponse(conn, BC_REQ_ERROR, conn->bc_errno, "", 1);
		return BC_INVALID_PACKET;
	}

	/*
		For each channel registered, send channel info to client.
	*/
	for (uint32_t i = 0; i < conn->bc_context->channel_count; i++)
	{
		/*
			If the channel isn't initialized, break.
		*/
		tempChannel = &conn->bc_context->channel_list[i];
		if (tempChannel->channel_id == 0)
		{
			break;
		}

		/*
			Make sure we don't have an integer overflow
		*/
		if ((channelNameSize = (uint32_t)strlen(tempChannel->channel_name)) >= UINT32_MAX - sizeof(*tempChannel) - 10) /* Let's be safe */
		{
			tempChannel->channel_name[UINT32_MAX - sizeof(*tempChannel) - 10] = 0;
			channelNameSize = UINT32_MAX - sizeof(*tempChannel) - 10;
		}

		respBufferSize = sizeof(tempChannel->channel_id) +
			sizeof(tempChannel->max_messages) +
			channelNameSize + 1;

		/*
			Allocate temporary response buffer.
		*/
		respBuffer = malloc(
			respBufferSize
		);
		if (!respBuffer)
			BcFatalError("Failed to allocate memory");

		/*
			Put channel members into the buffer
		*/
		memcpy(respBuffer, &tempChannel->channel_id, sizeof(tempChannel->channel_id));

		memcpy(respBuffer + sizeof(tempChannel->channel_id), &tempChannel->max_messages, sizeof(tempChannel->max_messages));

		strncpy_s(
			respBuffer + sizeof(tempChannel->channel_id) + sizeof(tempChannel->max_messages), 
			respBufferSize - sizeof(tempChannel->channel_id) - sizeof(tempChannel->max_messages),
			tempChannel->channel_name,
			respBufferSize - sizeof(tempChannel->channel_id) - sizeof(tempChannel->max_messages)
		);

		/*
			Send Response
		*/
		BcSendResponse(conn, packet->packet_id, BC_MORE_DATA, respBuffer, respBufferSize);

		free(respBuffer);
		respBuffer = NULL;
	}

	/*
		Send success when there is no more data
	*/
	BcSendResponse(conn, packet->packet_id, BC_SUCCESS, "", 1);

	return BC_SUCCESS;

}