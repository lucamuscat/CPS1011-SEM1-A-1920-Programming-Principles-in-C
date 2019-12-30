void printItem(Item *Item) {
  printf("\nSender: %s\n", Item->sender);
  printf("Subject: %s\n", Item->message->subject);
  printf("%s\n", Item->message->content);
  printf("Expiry: %llu\n", Item->expiry);
}
