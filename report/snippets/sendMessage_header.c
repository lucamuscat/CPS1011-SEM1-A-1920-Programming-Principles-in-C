/*
  Sends a message (enqueues a node) to all nodes or a specific node if
  an identifier is specified.

@param queue: MsgQs_t in which this function will operate.

@param identifier: If this is NULL, then the message is sent to all of
the queues (sendMessageBatch is sent). Otherwise it is directed to the
specified message queue

@param message: Message which will be sent.

@return: Return SEND_ERROR if identifier doesn't exist
*/
int sendMessage(MsgQs_t *q, void *identifier, char *message);
