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
			
			We convert to network order because it's better for clients to parse out.
			recv converts the data to the host system's endianness, but the integers don't get converted back with the data
		*/
		uint32_t nl_channel_id = htonl(tempChannel->channel_id);
		memcpy(respBuffer, &nl_channel_id, sizeof(nl_channel_id));

		uint32_t nl_max_messages = htonl(tempChannel->max_messages);
		memcpy(respBuffer + sizeof(nl_channel_id), &nl_max_messages, sizeof(nl_max_messages));

		strncpy_s(
			respBuffer + sizeof(nl_channel_id) + sizeof(nl_max_messages),
			respBufferSize - sizeof(nl_channel_id) - sizeof(nl_max_messages),
			tempChannel->channel_name,
			respBufferSize - sizeof(nl_channel_id) - sizeof(nl_max_messages)
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