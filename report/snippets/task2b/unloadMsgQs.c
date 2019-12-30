// Free everything.
void unloadMsgQs(MsgQs_t *q) {
  nodeMsg_t *node = q->front;
  free_node(node);
  q->size = 0;
}
