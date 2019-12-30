void sendMessageBatch(MsgQs_t *q, char *message) {
  for (size_t i = 0; i < q->index; ++i) {
    sendIndividualMessage(q->nodes[i], message);
  }
}
