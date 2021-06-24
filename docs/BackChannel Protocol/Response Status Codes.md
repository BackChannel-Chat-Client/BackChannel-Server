# Response status codes

| Code         | Name              | Description                                       |
| ------------ | ----------------- | ------------------------------------------------- |
| `0x00000000` | BC_SUCCESS        | Request was successful                            |
| `0xFFFFFFFF` | BC_REQ_ERROR      | There was an error in the request                 |
| `0x40000000` | BC_INVALID_PACKET | Request Packet was invalid                        |
| `0x40000001` | BC_UNIMPLEMENTED  | Request type specified is unimplemented           |
| `0x30000001` | BC_MORE_DATA      | There is more data that the client should receive | 
