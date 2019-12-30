int removeQ(nodeMsg_t *front, int identifier) {
  /*
	Are we on the rear node? If so return an error since the ID
	doesn't exist.
  */
  if (front->next == NULL)
    return -1;

  if (front->next->ID == identifier) {
    nodeMsg_t *next = front->next;
    next->size = 0;
    // Free all the Qs items
    free_item(next->front);
    // Replace the next node with the next node's next node.
    front->next = next->next;
    // free the memory allocated to the item pointers.
    free(next);
    return 1;
  }

  /*
    If the next node isn't null or an identifier, go to the next
    node to repeat the process. This way, the result will bubble
    back up the stack.
  */

  return removeQ(front->next, identifier);
}
