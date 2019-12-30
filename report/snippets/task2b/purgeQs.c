int purgeQs(MsgQs_t *q, void *identifier) {
  if (identifier == NULL) {
    empty_all_qs(q->front);
    return 1;
  }

  if (q->front->ID == (int)identifier) {
    nodeMsg_t *temp = q->front;
    free_item(temp->front);
    q->front = temp->next;
    return 1;
  }
  return empty_q(q->front, (int)identifier);
}
