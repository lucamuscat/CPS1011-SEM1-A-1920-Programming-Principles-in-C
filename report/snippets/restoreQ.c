int restoreQ(MsgQs_t *q, int identifier) {
  // search if identifier is in q
  for (size_t i = 0; i < q->index; ++i) {
    if (q->nodes[i]->ID == identifier)
      // return an error if found.
      return -1;
  }

  FILE *file;
  char filename[26];
  sprintf(filename, "%d.dat", identifier);
  if ((file = fopen(filename, "r")) == NULL) {
    puts("This identifier has never been persisted");
    return -1;
  }
  // snippet taken from https://c-for-dummies.com/blog/?p=1112
  char buffer[CHAR_LIMIT];
  char *message = buffer;
  size_t buffer_size = 256;
  createQ(q, identifier);
  while (getline(&message, &buffer_size, file) != -1) {
    sendMessage(q, (void *)identifier, message);
  }
  free(message);
}
