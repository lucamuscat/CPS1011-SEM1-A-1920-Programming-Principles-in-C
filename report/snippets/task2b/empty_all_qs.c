// Takes the front of a MsgQs_t.
void empty_all_qs(nodeMsg_t *front) {

  free_item(front->front);
  front->size = 0;
  if (front->next != NULL) {
    return empty_all_qs(front->next);
  }
  return;
}
