#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  This is going to try and implement rlp

*/

size_t byte_len(size_t number) {
  /*
    The logic behind this is simple. Since binary numbers are base
    2, we are applying log_2 on the number in order to get the
    number of bits needed to represent it. Flooring it will give us
    the the least possible value (look at it as a forced round down
    no matter what the fractional part is) and then we add by 1 so
    that any decimal value which was truncated can be made up for
    (not only that but you can't really represent a fraction of a
    bit). We are then dividing bit_len by 8 to get the number of
    bits needed and we are finding its ceiling (opposite of the
    floor, forced round up) This ensures that we always have enough
    bytes to represent all our bits.
*/
  double bit_len = floor(log2(number)) + 1.0;
  return ceil(bit_len / 8.0);
}

// Round byte_len up to a multiple of 2
size_t round_byte_len(size_t byte_len) { return byte_len + (byte_len % 2); }

void shift_chars(size_t start, char* buffer) {
	for (size_t i = strlen(buffer)+2; i > start+1; --i)
		buffer[i] = buffer[i-2];
	buffer[start] = buffer[start + 1] = ' ';
}

char* encode_length(size_t length, size_t offset) {
  if (length < 56) {
    // return length + offset;
  } else {
	  char* buffer;
    /*
	  Return in hex representation, each hex needs to represent a byte
	  ex. 0f ->\x0f, ff80 -> \xff\x80 needs number of bits needs to be
	  a multiple of 8.  allocate 2*2*byte_len(length) since \x is
	  being catted with every byte. Every byte is also represented by
	  2 one bit chars.  The list sizeof(char)*4 was added for the null
	  byte and the offset string representation.
    */
	  size_t byte_length = byte_len(length);
	  size_t precision = byte_length * 2;
	  size_t buffer_size = sizeof(char) * byte_length * 4 + sizeof(char)*4;

	  buffer = malloc(buffer_size);
	  char* temp = malloc(buffer_size);
	  // we are diving by to remove one of the * 2 associated with the \x
	  // and adding one for the initial \x
	  sprintf(temp, "\\x%0*x", precision, length);

	  /*
		i starts at 4 (5th element) due to the fact that the first 4
		elements are already properly formatted (ie. has "\x" and a
		hex byte representation).

		Steps by 4 since it has to skip the newly formatted hex byte.
	   */
	  for(size_t i = 4; i < strlen(temp)-1; i+=4){
		  shift_chars(i, temp);
		  temp[i] = '\\';
		  temp[i+1] = 'x';
	  }

	  sprintf(buffer, "\\%x%s", offset+byte_length, temp);
	  free(temp);
	  return buffer;
  }
}

/* /\* */
/*   Single bytes will have an encoding between [0x00, 0x7f], it is its own byte
 * encoding */
/* *\/ */
/* char* rlp_encode_string(char* input, char* buffer) { */
/* 	// A single byte with a null byte. */
/* 	char* result; */
/* 	size_t str_len = strlen(input); */
/* 	printf("%zu", bit_len(input)); */
/* 	if(str_len == 1 && result[0] < 0x80){ */
/* 		// self encoding */
/* 		return input; */
/* 	} else if(str_len > 1 && str_len <= 55) { */
/* 		// Added a char byte to hold null byte. */
/* 		buffer = malloc(str_len); */
/* 		return encode_length(str_len, 0x80); */
/* 	} */
/* 	// Encode a string larger than 55 bytes. */

/* } */

int main(void) {
  /* char *encoded_str; */
  /* rlp_encode_string("aaaa", encoded_str); */
  /* printf("%s", encoded_str); */
  /* free(encoded_str); */
	char *text = "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu";
	char *input = encode_length(strlen(text), 0xb7);
	printf("%s%s", input, text);
	free(input);
}
