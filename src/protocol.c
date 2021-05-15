#include "protocol.h"

BC_STATUS
BcParseRequest(char* buffer, size_t buffer_size, P_BC_PACKET packet)
{
	BC_PACKET temp_packet = { 0 };
	
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
		printf("\npacket size: %d\nbuffer_size: %d", temp_packet.packet_size, buffer_size);
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
	temp_packet.auth_key = _strdup(
								buffer + 
								sizeof(temp_packet.packet_size) + 
								sizeof(temp_packet.packet_id) + 
								sizeof(temp_packet.channel_id) + 
								sizeof(temp_packet.req_type) + 1);

	/*
		Get the request body
	*/
	temp_packet.req_body = _strdup(
								buffer + 
								sizeof(temp_packet.packet_size) + 
								sizeof(temp_packet.packet_id) + 
								sizeof(temp_packet.channel_id) + 
								sizeof(temp_packet.req_type) + 
								strlen(temp_packet.auth_key) + 2);

	*packet = temp_packet;
	
	return BC_SUCCESS;
}