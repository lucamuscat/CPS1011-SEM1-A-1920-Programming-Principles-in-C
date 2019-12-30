void free_individual_item(Item *Item) {
  free(Item->message->content);
  free(Item->message->subject);
  free(Item->message);
  free(Item->sender);
  free(Item);
}
