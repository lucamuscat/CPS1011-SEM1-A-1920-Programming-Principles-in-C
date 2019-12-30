
// Enqueue a MsgQs_t variable.
int createQ(MsgQs_t *q, int identifier) {
  if (contains_id(q->front, identifier))
    return -1;
  nodeMsg_t *tmp;
  tmp = malloc(sizeof(nodeMsg_t));
  // Setting the next pointer to null is important for the recursive
  // methods
  tmp->next = NULL;
  tmp->ID = identifier;
  tmp->size = 0;
  // A basic enqueue procedure.
  if (is_empty(q)) {
    q->front = tmp;
    q->rear = tmp;
  } else {
    q->rear->next = tmp;
    q->rear = tmp;
  }
  q->size++;
  return 1;
}
