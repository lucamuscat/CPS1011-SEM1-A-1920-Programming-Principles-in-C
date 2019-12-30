/*
  If the identifer is null, use sendMessageBatch, otherwise just send
  the message
*/
int sendMessage(MsgQs_t *q, void *identifier, char *message) {
  if (identifier == NULL)
    sendMessageBatch(q, message);
  for (size_t i = 0; i < q->index; ++i) {
    if ((int)identifier == q->nodes[i]->ID) {
      sendIndividualMessage(q->nodes[i], message);
      return SUCCESS;
    }
  }
  return IDENTIFIER_ERROR;
}
