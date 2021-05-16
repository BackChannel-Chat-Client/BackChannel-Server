#include "requests/BACKCHANNEL_REQ_GET_ERRNO.h"

BC_STATUS
BcReqGetErrno(P_BC_CONNECTION conn, P_BC_PACKET packet)
{
	if (!conn || !packet)
		return BC_INVALID_PARAM;

	if (!conn->sock)
		return BC_NOT_CONNECTED;

	if (BcVerifyPacket(packet) != BC_SUCCESS)
	{
		conn->bc_errno = BC_INVALID_PACKET;
		BcNetSendUint32(conn, BACKCHANNEL_REQ_ERROR);
		return BC_INVALID_PACKET;
	}

	BcNetSendUint32(conn, conn->bc_errno);
}