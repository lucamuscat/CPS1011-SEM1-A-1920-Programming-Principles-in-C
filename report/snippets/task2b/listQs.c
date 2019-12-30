// List everything.
void listQs(nodeMsg_t *front) {
  if (front->size == 0) {
    puts("This is empty :/");
  } else {
    printf("\nID: %d", front->ID);
    listItems(front->front);
  }
  if (front->next != NULL) {
    return listQs(front->next);
  }
  return;
}
