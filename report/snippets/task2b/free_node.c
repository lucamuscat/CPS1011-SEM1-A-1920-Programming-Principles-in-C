// Free everything using tail-recursion.  This way, we won't need a
// pointer to the previous element Since all we need to do is go back
// up the stack.
void free_node(nodeMsg_t *node) {
  if (node->next != NULL)
    free_node(node->next);
  free_item(node->front);
  free(node);
  return;
}
