#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  The offsets and values needed were taken off the RLP ethereum wiki
  provided in the footnote of the assignment.
*/

size_t byte_len(size_t number) {
  /*
    The logic behind this is simple. Since binary numbers are base 2,
    we are applying log_2 on the number in order to get the number of
    bits needed to represent it. Flooring it will give us the the
    least possible value (look at it as a forced round down no matter
    what the fractional part is) and then we add by 1 so that any
    decimal value which was truncated can be made up for (not only
    that but you can't really represent a fraction of a bit). We are
    then dividing bit_len by 8 to get the number of bits needed and we
    are finding its ceiling (opposite of the floor, forced round up)
    This ensures that we always have enough bytes to represent all our
    bits.
*/
  double bit_len = floor(log2(number)) + 1.0;
  return ceil(bit_len / 8.0);
}

/*
  This method will be used to encode objects with a payload larger
  than 55 bytes. The flexibility of this method comes from encoding
  both strings and arrays.
*/
char *encode_long_object(size_t length, char offset) {
  size_t byte_length = byte_len(length); // +2 to hold the offset and the null byte.
  size_t buffer_size = sizeof(char) * (byte_length + 2);
  char *buffer = malloc(buffer_size);
  // dont forget to free
  buffer[0] = offset + byte_length;
  buffer[buffer_size - 1] = '\0';
  size_t j = 0;
  for (size_t i = buffer_size - 2; i > 0; --i, ++j)
    buffer[i] = length >> (8 * j);
  return buffer;
}
// return the number of bytes returned in order to avoid strlen.
char *str_encode_length(size_t length) {
  size_t byte_length = byte_len(length);
  char *buffer;
  char offset;
  if (length < 56) {
    offset = 0x80;
    buffer = malloc(sizeof(unsigned char) * 2);
    buffer[0] = length + offset;
    buffer[1] = '\0';
    return buffer;
  } else {
    offset = 0xb7;
    return encode_long_object(length, offset);
  }
  return NULL;
}

// Returns the size of the rlp encoded string.
size_t rlp_strlen(char *string) {
  size_t length = strlen(string);
  if (length < 56)
    return length + 2;
  // We are adding one for the offset
  return length + byte_len(length) + 2;
}

void rlp_encode_str(char *dest, char *src) {
  size_t size = strlen(src);
  /*
	If the size if one, the message is self encoding.  If the size
	is less than 56 and not 1, the encoding The encoding will be the
	offset 0x80 + the size. Otherwise, use the encode_long_object method.
  */
  if (size == 1) {
    dest[0] = src[0];
    dest[1] = '\0';
  } else if (size < 56) {
    dest[0] = 0x80 + size;
    dest[1] = '\0';
  } else {
    strcpy(dest, encode_long_object(size, 0xb7));
  }
  strcat(dest, src);
}

char *rlp_encode_list(size_t length) {
  char *buffer;
  if (length < 56) {
    buffer = malloc(sizeof(char) * 2);
    buffer[0] = 0xc0 + length;
    buffer[1] = '\0';
    return buffer;
  } else {
    return encode_long_object(length, 0xf7);
  }
  return NULL;
}
