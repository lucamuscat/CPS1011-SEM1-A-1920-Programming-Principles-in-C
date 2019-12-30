int deleteQ(MsgQs_t *q, int identifier) {
  if (q->front->ID == identifier) {
    nodeMsg_t *temp = q->front;
    free_item(temp->front);
    q->front = temp->next;
    return 1;
  }
  return removeQ(q->front, identifier);
}
