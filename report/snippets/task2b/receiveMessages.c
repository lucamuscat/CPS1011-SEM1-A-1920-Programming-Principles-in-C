int receiveMessages(MsgQs_t *q, int identifier, size_t num_of_messages) {
  nodeMsg_t *front = q->front;
  /*
	Find the node which the ID belongs to.  Make sure that the
	num_of_messages doesn't skip the max number of messages.  Once
	found, display its contents, free it and do a normal dequeue
	procedure.

  */

  for (size_t i = 0; i < q->size; ++i) {
    if (front->ID == identifier) {
      num_of_messages =
          num_of_messages > front->size ? front->size : num_of_messages;
      Item *front_item;
      for (size_t j = 0; j < num_of_messages; ++j) {
        // Link the front to the next item.
        front_item = front->front;
        printItem(front_item);
        free_individual_item(front_item);
        front->front = front_item->next;
        front->size--;
      }
      return 1;
    } else {
      front = front->next;
    }
  }
  return -1;
}
