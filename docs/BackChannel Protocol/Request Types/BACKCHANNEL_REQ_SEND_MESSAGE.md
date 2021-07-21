# Request `0x11`: BACKCHANNEL_REQ_SEND_MESSAGE

## Request Parameters

**Channel ID (`channel_id`)**:
Channel to send message to.

**Authentication key (`auth_key`)**: 
User's authentication key.

**Request Body (`req_body`)**:
Message to send to channel

## Response Parameters
Check the status code for success.

In the response body, the message ID for the newly created message is stored as binary data. See table below for details.

| Data                          | Type                         | Description                                |
| ----------------------------- | ---------------------------- | ------------------------------------------ |
| Message ID     | 32-bit unsigned integer      | The ID for the newly created message                     |


