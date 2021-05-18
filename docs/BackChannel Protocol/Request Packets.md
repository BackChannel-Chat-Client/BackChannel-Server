# Request Packets
Request packets are sent to the BackChannel server to interact with the server and its clients.

## Packet Structure

A basic packet sent to the BackChannel server is as follows

| Field                            | Type                         | Value                                                                                                                                                        |
| -------------------------------- | ---------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Packet Size (`packet_size`)      | 32-bit unsigned integer      | The size of the packet info, keys, and body                                                                                                                  |
| Packet ID (`packet_id`)          | 32-bit unsigned integer      | An ID chosen by the client to identify the request/response. The server will respond with the ID given, or `BACKCHANNEL_REQ_ERROR` (-1) if there was an error. |
| Channel ID (`channel_id`)        | 32-bit unsigned integer      | The channel ID to make the request to. Use channel ID `0` to make a request to the server itself.                                                            |
| Request Type (`req_type`)        | 8-bit unsigned char          | The type of request being made. See [[#Request Types]] below.                                                                                                |
| Authentication Keys (`auth_key`) | NULL-Terminated ASCII string | The authentication keys for the server. TODO: What am I doing.                                                                                               |
| Request Body (`req_body`)        | NULL-Terminated ASCII string | The request body                                                                                                                                             |

This can be represented in C as

```C
/*
	Taken from include/protocol.h
	Credit to hypervis0r
*/
#include <stdint.h>
typedef struct _BC_PACKET
{
	uint32_t	packet_size;
	uint32_t	packet_id;
	uint32_t	channel_id;
	uint8_t		req_type;
	char*		auth_key;
	char*		req_body;
} BC_PACKET, *P_BC_PACKET;
```

### Packet Size
The packet size member is used to find the size of the packet in total. This includes the `packet_size` member, the total size of the `auth_key` buffer, and the total size of the `req_body` buffer. 

The minimum size this member can be is ***15 bytes***, 13 bytes for the integral members, and 2 bytes for the null characters in the `auth_key` and `req_body` buffers.

This member can be found in C as
```C
packet_size = 13 + strlen(auth_key) + 1 + strlen(req_body) + 1;
```

### Packet ID
The packet ID member is used to identify requests and responses to and from the BackChannel server. This ID is chosen by the client, and can be any value (although it is recommended to be chosen using random number generation).

The BackChannel server will respond with the packet ID given to indicate a successful request, or it will respond with `BACKCHANNEL_REQ_ERROR` (0xFFFFFFFF) if there is an error with the request.

### Channel ID
The channel ID member is used to specify which channel to make the request to. Use channel ID `0` to send requests to the server itself.

### Request Types
There are many different requests that can be made to the BackChannel server and its channels.
See [[BackChannel Protocol Request Types]].

### Authentication Keys
TODO: Encryption

For now just set this to be a single NULL byte.

### Request Body
