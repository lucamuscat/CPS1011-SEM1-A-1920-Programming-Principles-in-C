int receiveMessages(MsgQs_t *q, int identifier, size_t num_of_messages) {
  node *node;
  for (size_t i = 0; i < q->index; ++i) {
    if (q->nodes[i]->ID == identifier) {
      node = q->nodes[i];
    }
  }
  if (node == NULL)
    return -1;
  // Print it then free it.
  while (node->index > 0 && num_of_messages > 0) {
    printf("%d: %s", node->index, node->messages[node->index - 1]);
    free(node->messages[node->index]);
    node->index--;
    num_of_messages--;
  }
  return SUCCESS;
}
