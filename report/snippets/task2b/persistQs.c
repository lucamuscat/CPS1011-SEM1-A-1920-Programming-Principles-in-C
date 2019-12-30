int persistQ(MsgQs_t *MsgQ, int identifier) {
  /*
    The strings are already RLP encoded. The only thing that needs to
    be taken care of is the encoding of the expiry.

    Create a function which takes care of the list representation
    of nodeMsg_t (just get the payload size ie. go through the
    Item queue and get their sizes); Every time a function
    finishes, its result is directly written into the file. Once
    the list representation has been written, the sender and
    expiry are written, followed by the list representation of the
    message and its dumped text.

    This whole algorithm will be encapsulated into a function
  */

  // Go through all the nodes
  /*
    This is necessary as opposed to taking the size of the stored
    chars since the stored chars are already encoded.
  */

  nodeMsg_t *q;
  nodeMsg_t *tmp = MsgQ->front;
  // Find the node with the matching ID
  if (contains_id(MsgQ->front, identifier)) {
    for (size_t i = 0; i < MsgQ->size; ++i) {
      if (tmp->ID == identifier) {
        q = tmp;
      } else {
        tmp = tmp->next;
      }
    }
  } else {
    return -1;
  }

  q->bytes = update_node_bytes(q->front);
  // https://stackoverflow.com/questions/14564813/how-to-convert-integer-to-character-array-using-c
  // 10 max decimal digits with 32 bits (4 byte int)
  // 4 extra to hold ".dat"
  // 1 extra for the null byte.
  FILE *file;
  char file_name[15];
  sprintf(file_name, "%d.dat", q->ID);
  if ((file = fopen(file_name, "w")) == NULL) {
    printf("ERROR OPENING %s", file_name);
    fclose(file);
    return -1;
  }
  char *list_encoding = rlp_encode_list(q->bytes);
  fwrite(rlp_encode_list(q->bytes), sizeof(char), strlen(list_encoding), file);
  Item *front = q->front;
  // This loop writes out everything into a file.
  for (size_t i = 0; i < q->size; ++i) {
    char *item_encoding = rlp_encode_list(front->bytes);
    fwrite(item_encoding, sizeof(char), strlen(item_encoding), file);
    fwrite(front->sender, sizeof(char), strlen(front->sender), file);
    char *expiry_encoding = str_encode_length(byte_len(front->expiry));
    fwrite(expiry_encoding, sizeof(char), strlen(expiry_encoding), file);
    fwrite(&front->expiry, sizeof(long int), 1, file);
    char *message_encoding = rlp_encode_list(front->message->bytes);
    fwrite(message_encoding, sizeof(char), strlen(message_encoding), file);
    char *subject = front->message->subject;
    char *content = front->message->content;
    fwrite(subject, sizeof(char), strlen(subject), file);
    fwrite(content, sizeof(char), strlen(content), file);
    front = front->next;
  }
  fclose(file);
  return 1;
}
