#include "requests/BACKCHANNEL_REQ_SEND_MESSAGE.h"

BC_STATUS
BcReqSendMessage(P_BC_CONNECTION conn, P_BC_REQ_PACKET packet)
{
	P_BC_CHANNEL channel = NULL;
	uint32_t messageCount = 0;
	char respBuffer[5] = { 0 }; /* Buffer to store response message ID in */

	if (!conn || !packet)
		return BC_INVALID_PARAM;

	if (!conn->sock)
		return BC_NOT_CONNECTED;

	if (!conn->bc_context)
		return BC_INVALID_CONTEXT;

	if (!conn->bc_context->channel_list)
		return BC_INVALID_CONTEXT;

	if (BcVerifyRequestPacket(packet) != BC_SUCCESS)
		BcRequestFail(conn, BC_REQ_ERROR, BC_INVALID_PACKET);

	/*
		TODO: Verify auth key
		TODO: Timeouts
	*/

	/*
		Verify channel id is valid
	*/
	if (packet->channel_id >= conn->bc_context->max_channel_count || 
			packet->channel_id >= conn->bc_context->channel_count || 
			packet->channel_id == 0)
		BcRequestFail(conn, packet->packet_id, BC_INVALID_CHANNEL_ID);
	
	/*
		TODO: Is this safe?
	*/
	channel = &conn->bc_context->channel_list[packet->channel_id - 1];

	/*
		Check if channel is initialized
	*/
	if (channel->channel_id == 0 || channel->message_list == NULL)
		BcRequestFail(conn, packet->packet_id, BC_BAD_CHANNEL);

	/*
		Check if we have hit our limit of messages
	*/
	if (channel->message_count >= channel->max_messages)
		BcRequestFail(conn, packet->packet_id, BC_MESSAGE_LIMIT_HIT);

	messageCount = channel->message_count++;

	/*
		Add message to channel's message list
	*/
	channel->message_list[messageCount].id = channel->message_count;		/* Message ID */
	channel->message_list[messageCount].time_sent = time(NULL);				/* Message timestamp */
	
	channel->message_list[messageCount].body = strdup(packet->req_body);	/* Message Body */
	if (channel->message_list[messageCount].body == NULL)
	{
		--channel->message_count;
		BcRequestFail(conn, packet->packet_id, BC_SERVER_ERROR);
	}

	channel->message_list[messageCount].size = strlen(channel->message_list[messageCount].body) + 1; /* Message body size*/

	/*
		Copy new message ID into response buffer
	*/
	memcpy(respBuffer, &channel->message_list[messageCount].id, sizeof(channel->message_list[messageCount].id));
	
	BcSendResponse(conn, packet->packet_id, BC_SUCCESS, respBuffer, sizeof(respBuffer));
	return BC_SUCCESS;
}