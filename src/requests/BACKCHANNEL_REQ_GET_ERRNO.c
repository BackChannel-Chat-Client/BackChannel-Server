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
		BcSendResponse(conn, BACKCHANNEL_REQ_ERROR, conn->bc_errno, "", 1);
		return BC_INVALID_PACKET;
	}

	memcpy(resp_buffer, &conn->bc_errno, sizeof(conn->bc_errno));
	BcSendResponse(conn, packet->packet_id, BC_SUCCESS, resp_buffer, sizeof(resp_buffer));

	return BC_SUCCESS;
}