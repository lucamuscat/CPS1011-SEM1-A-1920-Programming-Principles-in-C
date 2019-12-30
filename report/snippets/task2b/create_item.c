Item *create_item(char *sender, char *subject, char *content) {
  Item *temp = malloc(sizeof(Item));
  temp->sender = malloc(sizeof(char) * rlp_strlen(sender));
  temp->message = malloc(sizeof(Message));
  temp->message->subject = malloc(sizeof(char) * rlp_strlen(subject));
  temp->message->content = malloc(sizeof(char) * rlp_strlen(content));
  // Plus 4 since time_t is an unsigned int which is 4 bytes.
  temp->bytes = strlen(sender) + strlen(subject) + strlen(content) + 4;
  temp->message->bytes = strlen(subject) + strlen(content);

  time(&temp->expiry);
  rlp_encode_str(temp->sender, sender);
  rlp_encode_str(temp->message->subject, subject);
  rlp_encode_str(temp->message->content, content);
  temp->next = NULL;

  return temp;
}
