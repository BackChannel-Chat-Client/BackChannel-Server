#ifdef _WIN32
	/* I hate MSVC */
	#define strdup _strdup
#endif

#include <stdint.h>
//#include "channels.h"

typedef uint32_t BC_STATUS;

#define BC_UNREFERENCED_PARAMETER(x) (x)

#define BC_SUCCESS 0
#define BC_ERROR 1
#define BC_INVALID_PARAM 2
#define BC_FILESYSTEM_ERROR 3
#define BC_INVALID_CONTEXT 4

/*
	TLS ERRNOs
*/
#define BC_TLS_ERROR	0xD0000000
#define BC_TLS_KEY_MISMATCH	0xD0000001
#define BC_TLS_NOT_CONNECTED 0xD0000002
#define BC_TLS_IO_ERROR	0xD0000003

/*
	Request ERRNOs
*/
#define BC_REQ_ERROR 0xFFFFFFFF
#define BC_INVALID_PACKET 0x40000000
#define BC_UNIMPLEMENTED 0x40000001
#define BC_SERVER_ERROR		0x40000002

/*
	Network ERRNOs
*/
#define BC_NETWORK_ERROR 0xB0000000
#define BC_NOT_CONNECTED 0xB0000001

/*
	Response ERRNOs
*/
#define BC_MORE_DATA	0x30000001

/*
	Channel ERRNOs
*/
#define BC_INVALID_CHANNEL_ID	0x50000000
#define BC_CHANNEL_LIMIT_HIT	0x50000001
#define BC_BAD_CHANNEL			0x50000002
#define BC_MESSAGE_LIMIT_HIT	0x50000003