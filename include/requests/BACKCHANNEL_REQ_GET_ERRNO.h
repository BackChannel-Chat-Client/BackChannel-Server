#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "common.h"

#include "networking.h"
#include "protocol.h"

/*
	Forward declaration of P_BC_CONNECTION.
	I hate compilers! I hate compilers!
*/
typedef struct _BC_CONNECTION* P_BC_CONNECTION;
typedef struct _BC_REQ_PACKET* P_BC_REQ_PACKET;

/*
	BACKCHANNEL_REQ_GET_ERRNO
	Sends the last BC_ERRNO value to the client
*/
BC_STATUS
BcReqGetErrno(P_BC_CONNECTION conn, P_BC_REQ_PACKET packet);