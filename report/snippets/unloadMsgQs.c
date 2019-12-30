void unloadMsgQs(MsgQs_t *q) {
  // free nodes and msgqs_t
  for (size_t i = 0; i < q->index; ++i) {
    for (size_t j = 0; j < q->nodes[i]->index; ++j) {
      free(q->nodes[i]->messages[j]);
    }
    free(q->nodes[i]);
  }
  free(q);
}
