MsgQs_t *initializeMsgQs() {
  MsgQs_t *q = (MsgQs_t *)malloc(sizeof(MsgQs_t));
  q->size = 0;
  q->front = NULL;
  q->rear = NULL;
  return q;
}
