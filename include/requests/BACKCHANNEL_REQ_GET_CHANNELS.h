#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "common.h"

#include "networking.h"
#include "protocol.h"
#include "context.h"
#include "channels.h"

/*
	Forward declaration of P_BC_CONNECTION.
	I hate compilers! I hate compilers!
*/
typedef struct _BC_CONNECTION* P_BC_CONNECTION;
typedef struct _BC_REQ_PACKET* P_BC_REQ_PACKET;

/*
	BACKCHANNEL_REQ_GET_CHANNELS
	Sends array of channel info to client
*/
BC_STATUS
BcReqGetChannels(P_BC_CONNECTION conn, P_BC_REQ_PACKET packet);