void batch_populate_node(nodeMsg_t *front, char *sender, char *subject,
                         char *content) {
  if (front == NULL)
    return;
  enqueue_nodeMsg_t(front, sender, subject, content);
  if (front->next != NULL)
    batch_populate_node(front->next, sender, subject, content);
  return;
}
