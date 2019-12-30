void listQs(MsgQs_t *q) {
  for (size_t i = 0; i < q->index; ++i) {
    printf("=========\nIdentifier: %d\n", q->nodes[i]->ID);
    if (q->nodes[i]->index == 0) {
      puts("This Message Queue is Empty :(");
      continue;
    }
    for (size_t j = 0; j < q->nodes[i]->index; ++j) {
      printf("%d: %s\n", j, q->nodes[i]->messages[j]);
    }
  }
}
