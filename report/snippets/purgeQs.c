
void purgeIndividualNode(node *node) {
  for (size_t i = 0; i < node->index; ++i) {
    free(node->messages[i]);
  }
  node->index = 0;
}

void purgeAllNodes(MsgQs_t *q) {
  for (size_t i = 0; i < q->index; ++i) {
    purgeIndividualNode(q->nodes[i]);
  }
}


int purgeQs(MsgQs_t *q, void *identifier) {
  // purge all
  if (identifier == NULL)
    purgeAllNodes(q);
  int int_id = (int)identifier;
  for (size_t i = 0; i < q->index; ++i) {
    if (int_id == q->nodes[i]->ID) {
      purgeIndividualNode(q->nodes[i]);
      return SUCCESS;
    }
  }
  return IDENTIFIER_ERROR;
}
