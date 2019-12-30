int populate_individual_node(nodeMsg_t *front, int ID, char *sender,
                             char *subject, char *content) {
  // Return an error if the first node is null.
  if (front == NULL)
    return -1;

  // If the ID's match, populate the node.
  if (front->ID == ID) {
    enqueue_nodeMsg_t(front, sender, subject, content);
    return 1;
  }

  /*
    Check if we aren't at the last node.  If we are, that means
    that the previous condition which checks for the Identifier
    failed
  */
  if (front->next != NULL)
    return populate_individual_node(front->next, ID, sender, subject, content);

  // The code can only reach this case if it is the last node in the linkedlist.

  return -1;
}
