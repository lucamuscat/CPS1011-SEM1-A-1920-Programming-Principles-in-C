
/*
  Skip the list encoding of the file by moving the file pointer
  accordingly.
*/

void skip_list(FILE *file) {
  unsigned char ch = fgetc(file);
  if (ch >= 0xc0 && ch <= 0xf7) {
    /*
      Self encoding list
      Since the encoding is only 1 byte long the next fgetc will get a valid
      char
    */
    return;
  } else if (ch >= 0xf8 && ch <= 0xff) {
    size_t byte_length = ch - 0xf7;
    while (byte_length > 0) {
      // Skip the byte characters representing the list length
      fgetc(file);
      byte_length--;
    }
  }
}

long int decode_expiry(FILE *file) {
  unsigned char ch = fgetc(file);
  long int temp;
  fread(&temp, sizeof(long int), 1, file);
  return temp;
}


/*
  Decode the string according to the character obtained.
  The algorithm followed can be found in the Ethereum RLP wiki.
*/
char *decode_string(FILE *file) {
  unsigned char ch = fgetc(file);
  char *buffer;
  if (ch < 0x80) {
    buffer = malloc(sizeof(char) * 2);
    buffer[0] = ch;
    buffer[1] = '\0';
    return buffer;
  } else if (ch >= 0x80 && ch < 0xb8) {
    // 0x7f instead of 0x80 due to the fact that if we get 0x80 and minus it by
    // 0x80 we will get a length of 0
    size_t length = ch - 0x80;
    buffer = malloc(sizeof(char) * length + 1);
    fread(buffer, sizeof(char), length, file);
    buffer[length] = '\0';
    return buffer;
  } else if (ch >= 0xb8 && ch < 0xbf) {
    size_t byte_length = ch - 0xb7;
    size_t size = 0;
    for (size_t i = 0; i < byte_length; ++i) {
      size |= fgetc(file) << 8 * (byte_length - 1 - i);
    }
    buffer = malloc(sizeof(char) * size);
    fread(buffer, sizeof(char), size, file);
    buffer[size] = '\0';
    return buffer;
  }
}
