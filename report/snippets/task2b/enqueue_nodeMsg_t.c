int enqueue_nodeMsg_t(nodeMsg_t *q, char *sender, char *subject,
                      char *content) {
  Item *tmp;
  tmp = create_item(sender, subject, content);
  // is the node not empty?
  if (q->size != 0) {
    q->rear->next = tmp;
    q->rear = tmp;
  } else {
    q->front = q->rear = tmp;
  }
  q->size++;
}
