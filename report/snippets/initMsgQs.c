MsgQs_t *initializeMsgQs() {
  // Initialize all of the nodes.
  MsgQs_t *q = (MsgQs_t *)malloc(sizeof(MsgQs_t));
  // Initialize the queue
  q->index = 0;
  return q;
}
