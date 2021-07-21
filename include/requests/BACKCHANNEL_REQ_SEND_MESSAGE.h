#pragma once

#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

#include "protocol.h"
#include "networking.h"

BC_STATUS
BcReqSendMessage(P_BC_CONNECTION conn, P_BC_REQ_PACKET packet);