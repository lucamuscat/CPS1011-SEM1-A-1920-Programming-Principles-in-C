// Empties a queue with a specific ID.
int empty_q(nodeMsg_t *front, int identifier) {

  if (front->next == NULL)
    return -1;

  if (front->next->ID == identifier) {
    nodeMsg_t *next = front->next;
    next->size = 0;
    // Free all the Qs items
    free_item(next->front);
    return 1;
  }

  /*
    If the next node isn't null or an identifier, go to the next
    node to repeat the process. This way, the result will bubble
    back up the stack.
  */
  return empty_q(front->next, identifier);
}
