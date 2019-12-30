int createQ(MsgQs_t *q, int identifier) {
  if (q->index < QUEUE_LIMIT) {
    q->nodes[q->index] = malloc(sizeof(node));
    q->nodes[q->index]->index = 0;
    q->nodes[q->index]->ID = identifier;
    q->index++;
    return SUCCESS;
  }
  return ENQUEUE_ERROR;
}
