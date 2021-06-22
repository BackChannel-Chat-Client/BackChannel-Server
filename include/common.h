#include <stdint.h>
//#include "channels.h"

typedef uint32_t BC_STATUS;

#define BC_UNREFERENCED_PARAMETER(x) (x)

#define BC_SUCCESS 0
#define BC_ERROR 1
#define BC_INVALID_PARAM 2
#define BC_FILESYSTEM_ERROR 3
#define BC_INVALID_CONTEXT 4
#define BC_CHANNEL_LIMIT_HIT 5

/*
	Request ERRNOs
*/
#define BC_REQ_ERROR 0xFFFFFFFF
#define BC_INVALID_PACKET 0x40000000
#define BC_UNIMPLEMENTED 0x40000001

/*
	Network ERRNOs
*/
#define BC_NETWORK_ERROR 0xB0000000
#define BC_NOT_CONNECTED 0xB0000001

#define BC_MORE_DATA	0x30000001