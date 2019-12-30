int sendMessage(MsgQs_t *q, void *ID, char *sender, char *subject,
                char *content) {
  // If the provided ID is null, treat it as unspecified and use sendMessageBatch.
  // otherwise, sendMessage to a single nodeMsg_t (if it exists ofcourse).
  if (ID == NULL) {
    sendMessageBatch(q, sender, subject, content);
    return 1;
  }
  return populate_individual_node(q->front, (int)ID, sender, subject, content);
}
