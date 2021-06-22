#include "requests/BACKCHANNEL_REQ_GET_ERRNO.h"

BC_STATUS
BcReqGetErrno(P_BC_CONNECTION conn, P_BC_REQ_PACKET packet)
{
	char resp_buffer[sizeof(conn->bc_errno) + 1] = { 0 };
	
	if (!conn || !packet)
		return BC_INVALID_PARAM;

	if (!conn->sock)
		return BC_NOT_CONNECTED;

	if (BcVerifyRequestPacket(packet) != BC_SUCCESS)
	{
		conn->bc_errno = BC_INVALID_PACKET;
		BcSendResponse(conn, BC_REQ_ERROR, conn->bc_errno, "", 1);
		return BC_INVALID_PACKET;
	}

	/*
		Put the raw errno into the buffer.
		We don't worry about adding the null byte because it's added when we init
		the buffer. (Or maybe we should worry?)
	*/
	memcpy(resp_buffer, &conn->bc_errno, sizeof(conn->bc_errno));
	BcSendResponse(conn, packet->packet_id, BC_SUCCESS, resp_buffer, sizeof(resp_buffer));

	return BC_SUCCESS;
}