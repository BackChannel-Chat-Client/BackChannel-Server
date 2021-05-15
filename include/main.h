#include <stdlib.h>
#include <stdio.h>

#include "networking.h"
#include "log.h"


#define BC_SUCCESS 0
#define BC_ERROR -1
#define BC_NETWORK_ERROR -2
#define BC_INVALID_PARAM -3
#define BC_UNIMPLEMENTED -4
#define BC_INVALID_PACKET -5

typedef int BC_STATUS;