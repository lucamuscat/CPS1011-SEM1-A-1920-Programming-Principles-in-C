/*
  Clears a node from all of its messages, just loop through all of the
  messages and place a \0 at the very beginning.
  @param queue: MsgQs_t on which this function will operate.
  @param indetifier: Identifier of node to clear.
*/
int purgeQs(MsgQs_t *q, void *indentifier);
