#include <stdint.h>

typedef uint32_t BC_STATUS;

#define BC_SUCCESS 0
#define BC_ERROR 1
#define BC_INVALID_PARAM 2
#define BC_FILESYSTEM_ERROR 3

/*
	Request ERRNOs
*/
#define BACKCHANNEL_REQ_ERROR 0xFFFFFFFF
#define BC_INVALID_PACKET 0x40000000
#define BC_UNIMPLEMENTED 0x40000001

/*
	Network ERRNOs
*/
#define BC_NETWORK_ERROR 0xB0000000
#define BC_NOT_CONNECTED 0xB0000001