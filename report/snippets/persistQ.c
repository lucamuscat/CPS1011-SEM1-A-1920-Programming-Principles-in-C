
int persistQ(MsgQs_t *q, int identifier) {
  node *node;
  for (size_t i = 0; i < q->index; ++i) {
    // Go through all the nodes and check their ID
    if (q->nodes[i]->ID == identifier)
      node = q->nodes[i];
  }
  if (node == NULL)
    return -1;

  FILE *file;
  char filename[26];
  sprintf(filename, "%d.dat", identifier);
  if ((file = fopen(filename, "w")) == NULL) {
    printf("ERROR OPENING %s", filename);
    fclose(file);
    return -1;
  }
  for (size_t i = 0; i < node->index; ++i) {
	// Go through each node and place it in the file, seperated by a
	// new line.
    fputs(strcat(node->messages[i], "\n"), file);
  }
  // Close the stream
  fclose(file);
  return SUCCESS;
}
