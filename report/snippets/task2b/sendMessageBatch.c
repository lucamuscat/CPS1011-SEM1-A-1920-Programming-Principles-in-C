// returns an error if queue id doesn't exist
void sendMessageBatch(MsgQs_t *q, char *sender, char *subject, char *content) {
  batch_populate_node(q->front, sender, subject, content);
}
