
// Precondition: MsgQs_t is created from before hand.
int restoreQ(MsgQs_t *q, int identifier) {
  FILE *file;
  char file_name[15];
  sprintf(file_name, "%d.dat", identifier);
  if ((file = fopen(file_name, "r")) == NULL) {
    printf("ERROR OPENING %s", file_name);
    fclose(file);
    return -1;
  }
  skip_list(file);
  char *sender;
  long int expiry;
  char *subject;
  char *content;

  // Decoding this takes a specific pattern.
  // Analyze a .dat file which is produced by the code
  // to see it.
  while (!feof(file)) {
    skip_list(file);
    if (!feof(file)) {
      sender = decode_string(file);
      expiry = decode_expiry(file);
      skip_list(file);
      subject = decode_string(file);
      content = decode_string(file);
      sendMessage(q, (void *)identifier, sender, subject, content);
    }
  }
}
