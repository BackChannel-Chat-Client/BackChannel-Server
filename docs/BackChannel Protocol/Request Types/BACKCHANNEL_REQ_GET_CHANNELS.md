# Request `0x10`: BACKCHANNEL_REQ_GET_CHANNELS

## Request Parameters
**Authentication key (`auth_key`)**: 
User's authentication key.

## Response Parameters
This request will send multiple responses for each channel available to the user. The client can determine if there is more data to be sent by checking the status code of the response. If the status code is [[Response Status Codes|BC_MORE_DATA]], keep receiving until the status code is [[Response Status Codes|BC_SUCCESS]].

In the response body, the info on the channels is stored in binary data.
The data sent is structured as follows:

| Data                          | Type                         | Description                                |
| ----------------------------- | ---------------------------- | ------------------------------------------ |
| Channel ID (`channel_id`)     | 32-bit unsigned integer      | The ID for the channel                     |
| Max messages (`max_messages`) | 32-bit unsigned integer      | The max number of messages for the channel |
| Channel name (`channel_name`) | NULL-Terminated ASCII string | The name of the channel |
