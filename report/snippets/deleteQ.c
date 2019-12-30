
int deleteQ(MsgQs_t *q, int identifier) {
  for (size_t i = 0; i < q->index; ++i) {
    if (q->nodes[i]->ID == identifier) {
      free(q->nodes[i]);
      // Final node in queue
      if (i == q->index) {
        q->index--;
      } else {
        // Not final node in queue
        // Shift following nodes back by 1.
        for (size_t j = i; j < q->index - 1; ++j) {
          q->nodes[i] = q->nodes[i + 1];
        }
        // free the last node since this was already shifted
        // one back
        free(q->nodes[q->index]);
        q->index--;
      }
      return 0;
    }
  }
  return DEQUEUE_ERROR;
}
