#include "protocol.h"

BC_STATUS
BcParseRequest(char* buffer, size_t buffer_size, P_BC_REQ_PACKET packet)
{
	BC_REQ_PACKET temp_packet = { 0 };
	
	/*
		We check the buffer_size parameter because we copy
		at least `sizeof(temp_packet.packet_size)` from the buffer.
		Without this check we may have some issues.
	*/
	if (!packet || !buffer || buffer_size < sizeof(temp_packet.packet_size))
		return BC_INVALID_PARAM;
	
	/*
		Get the packet size
	*/
	memcpy(
		&(temp_packet.packet_size), 
		buffer, 
		sizeof(temp_packet.packet_size));

	/*
		If the packet size is inconsistent, we have a problem and need to stop.
		Otherwise, we assume the content we receive from now is valid. We'll check stuff
		once the data hits its respective functions
	*/
	if (temp_packet.packet_size < buffer_size || temp_packet.packet_size > buffer_size)
	{
		printf("\npacket size: %d\nbuffer_size: %zu\n", temp_packet.packet_size, buffer_size);
		BcError("Packet Size Invalid");
		return BC_INVALID_PACKET;
	}

	/*
		Get the packet ID
	*/
	memcpy(
		&(temp_packet.packet_id), 
		buffer+sizeof(temp_packet.packet_size), 
		sizeof(temp_packet.packet_id));

	/*
		Get the channel ID
	*/
	memcpy(
		&(temp_packet.channel_id),
		buffer + sizeof(temp_packet.packet_size) + sizeof(temp_packet.packet_id),
		sizeof(temp_packet.channel_id));

	/*
		Get the request type
	*/
	memcpy(
		&(temp_packet.req_type),
		buffer + sizeof(temp_packet.packet_size) + sizeof(temp_packet.packet_id) + sizeof(temp_packet.channel_id),
		sizeof(temp_packet.req_type));

	/*
		Get the auth key
	*/
	temp_packet.auth_key = strdup(
								buffer + 
								sizeof(temp_packet.packet_size) + 
								sizeof(temp_packet.packet_id) + 
								sizeof(temp_packet.channel_id) + 
								sizeof(temp_packet.req_type) + 1);

	/*
		Get the request body
	*/
	temp_packet.req_body = strdup(
								buffer + 
								sizeof(temp_packet.packet_size) + 
								sizeof(temp_packet.packet_id) + 
								sizeof(temp_packet.channel_id) + 
								sizeof(temp_packet.req_type) + 
								strlen(temp_packet.auth_key) + 2);

	*packet = temp_packet;
	
	return BC_SUCCESS;
}

BC_STATUS
BcVerifyRequestPacket(P_BC_REQ_PACKET packet)
{
	if (!packet)
		return BC_INVALID_PARAM;

	/*
		If the packet size is less than the minimum,
		we have a problem
	*/
	if (packet->packet_size < BC_MINIMUM_REQUEST_PACKET_SIZE)
		return BC_INVALID_PACKET;

	/*
		If auth_key and req_body are NULL,
		we have a problem
	*/
	if (!packet->auth_key || !packet->req_body)
		return BC_INVALID_PACKET;

	return BC_SUCCESS;
}

BC_STATUS
BcHandleRequest(P_BC_CONNECTION conn, P_BC_REQ_PACKET packet)
{
	/*
		Validate parameters
	*/
	if (!conn || !packet)
		return BC_INVALID_PARAM;

	/*
		Check if connected
	*/
	if (!conn->sock)
		return BC_NOT_CONNECTED;

	/*
		Verify the request packet
	*/
	if (BcVerifyRequestPacket(packet) != BC_SUCCESS)
	{
		conn->bc_errno = BC_INVALID_PACKET;
		BcNetSendUint32(conn, conn->bc_errno);
		
		return BC_INVALID_PACKET;
	}

	/*
		Handle the request
		TODO: This switch statement is gonna get pretty large, but it's probably fine
	*/
	switch (packet->req_type)
	{
		case BACKCHANNEL_REQ_GET_ERRNO:
			BcReqGetErrno(conn, packet);
			break;
		default: /* Unimplemented request */
			conn->bc_errno = BC_UNIMPLEMENTED;
			BcNetSendUint32(conn, conn->bc_errno);
		
			return BC_UNIMPLEMENTED;
	}

	return BC_SUCCESS;
}

#ifdef FUCK_ME
BC_STATUS
BcSendResponse(P_BC_CONNECTION conn, uint32_t packet_id, uint32_t resp_status, char* resp_body)
{
	if (!resp_body || !conn)
		return BC_INVALID_PARAM;

	if (!conn->sock)
		return BC_NOT_CONNECTED;

	if (strlen(resp_body) >= UINT32_MAX - BC_MINIMUM_RESPONSE_PACKET_SIZE)
		resp_body[UINT32_MAX - BC_MINIMUM_RESPONSE_PACKET_SIZE] = 0;

	uint32_t resp_size = BC_MINIMUM_RESPONSE_PACKET_SIZE + (uint32_t)strlen(resp_body);

	char* send_buffer = malloc(resp_size);
	if (!send_buffer)
	{
		BcError("Failed to allocate response packet");

		return BC_ERROR;
	}

	/*
		Response Packet Size
	*/
	memcpy(send_buffer, &resp_size, sizeof(resp_size));
		
	/*
		Packet ID
	*/
	memcpy(send_buffer + sizeof(resp_size), &packet_id, sizeof(packet_id));

	/*
		Response status
	*/
	memcpy(send_buffer + sizeof(resp_size) + sizeof(packet_id), &resp_status, sizeof(resp_status));

	/*
		Response body
	*/
	memcpy(send_buffer + sizeof(resp_size) + sizeof(packet_id) + sizeof(resp_status), resp_body, strlen(resp_body)+1);

	/*
		TODO: send takes an int as input. This may be an issue if the resp_size
			is bigger than INT_MAX, and also if the int type isn't 4 bytes on the compiled system
	*/
	send(conn->sock, send_buffer, resp_size, 0);

	free(send_buffer);
}
#endif