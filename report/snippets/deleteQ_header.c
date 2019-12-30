/*
  When a queue is deleted, it will simply be overwritten by the
  following queues. If it's the last node, set it as null. If each
  node is also malloced and the individual queues are freed, that
  means that the max number of queues will decrease each time.

  @return: Returns DELETE_ERROR if the queue identifier doesn't exist.
*/
int deleteQ(MsgQs_t *q, int indentifier);
