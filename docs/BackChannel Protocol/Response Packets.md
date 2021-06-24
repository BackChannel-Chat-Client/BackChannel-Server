# Response Packets
This packet is sent from the BackChannel server to the client in response to a [[Request Packets]].

## Packet Structure
| Field                           | Type                         | Value                                |
| ------------------------------- | ---------------------------- | ------------------------------------ |
| Packet Size (`packet_size`)     | 32-bit unsigned integer      | The size of the packet info and body |
| Packet ID (`packet_id`)         | 32-bit unsigned integer      | The packet ID of the request packet  |
| Response Status (`resp_status`) | 32-bit unsigned integer      | The status code of the request       |
| Response Body (`resp_body`)     | NULL-Terminated binary data | The response body                    |

This can be represented in C as

```C
/*
	Taken from include/protocol.h
	Credit to hypervis0r
*/
#include <stdint.h>
typedef struct _BC_RESP_PACKET
{
	uint32_t 	packet_size;
	uint32_t 	packet_id;
	uint32_t 	resp_status;
	char*		resp_body
} BC_RESP_PACKET, *P_BC_RESP_PACKET
```

### Packet Size
The packet size member is used to find the size of the packet in total. This includes the `packet_size` member and the total size of the `req_body` buffer. 

The minimum size this member can be is ***13 bytes***, 12 bytes for the integral members, and 1 byte for the null character in the `resp_body` buffer.

This member can be found in C as
```C
packet_size = 12 + strlen(resp_body) + 1;
```

### Packet ID
The packet ID member is used to identify requests and responses to and from the BackChannel server. This ID is chosen by the client, and can be any value (although it is recommended to be chosen using random number generation).

This member will be set to the packet ID of the [[Request Packets|request packet]] to ensure the client knows which request the BackChannel server is responding to.

### Response Status
This member is set to the status of the request. If this member is non-zero, then there was an error with the request. See [[Response Status Codes]] for more details.

### Response Body
Depending on the request type, the response may contain a body. Refer to [[BackChannel Protocol Request Types]] for more details.

If the request type specified does not need a response body, this value will be set to `"\x00"` .