#include "basic_queue.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUMMY_TEXT "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse eu massa eu diam interdum laoreet. Integer lectus turpis, convallis et lorem eu, dignissim facilisis nisl. Nunc sollicitudin purus sed nunc facilisis tincidunt. Nunc porta nunc a ex tincidunt dapibus. Sed consectetur nisl vel lacus sollicitudin pretium. Cras faucibus nunc eu est rhoncus, id pulvinar nisl vulputate. Quisque at mauris velit. Fusce fermentum finibus finibus. Phasellus euismod nec enim id facilisis. Maecenas id lectus nunc. Integer fringilla lectus lorem, ac ullamcorper lectus pretium at. Sed felis lectus, auctor sed egestas non, rutrum non urna. Vestibulum nec euismod erat. Nam viverra nec lacus quis accumsan. Aliquam sodales bibendum tellus.Proin hendrerit purus ut ornare sollicitudin. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec dapibus nec ligula vel condimentum. Donec in elit et eros iaculis accumsan in vel nibh. Nulla massa massa, laoreet non imperdiet eget, cursus eget amet."

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
char* encode_long_object(size_t length, char offset){
	size_t byte_length = byte_len(length);	// +2 to hold the offset and the null byte.
	size_t buffer_size = sizeof(char)*(byte_length+2);
	char* buffer = malloc(buffer_size);
	// dont forget to free
	buffer[0] = offset + byte_length;
	buffer[buffer_size-1] = '\0';
	size_t j = 0;
	for(size_t i = buffer_size-2; i > 0; --i, ++j)
		buffer[i] = length>>(8*j);
	return buffer;
}
char* str_encode_length(size_t length) {
	size_t byte_length = byte_len(length);
	char* buffer;
	char offset;
	if (length < 56) {
		offset = 0x80;
		buffer = malloc(sizeof(unsigned char)*2);
		buffer[0] = length + offset;
		buffer[1] = '\0';
		return buffer;
	} else {
		offset = 0xb7;
		return encode_long_object(length, offset);
	}
	return NULL;
}
void encode_q(node* Queue, char* buffer) {
	for (size_t i = 0; i < Queue->index; ++i) {
		char* message = Queue->messages[i];
		strcat(buffer, str_encode_length(strlen(message)));
		strcat(buffer, message);
	}
}
char* str_encode_node(node* Queue) {
	// find total number of bytes
	char* buffer;
	size_t accumulator = 0;
	for (size_t i = 0; i < Queue->index; ++i) {
		accumulator += strlen(Queue->messages[i]);
	}
	size_t total_bytes = accumulator*sizeof(char)+sizeof(int)*2;
	buffer = malloc(total_bytes);
	char offset = 0x7f;
	if(total_bytes >= 56){
		char* encoding = encode_long_object(total_bytes, offset);
		strcpy(buffer, encoding);
		free(encoding);
		encode_q(Queue, buffer);
		return buffer;
	}
	offset = 0xc0;
	buffer[0] = offset + accumulator;
	buffer[1] = '\0';
	encode_q(Queue, buffer);
	return buffer;
}
int main(void) {
	char* object = encode_long_object(strlen(DUMMY_TEXT), 0xb7);
	MsgQs_t *q = initializeMsgQs();
	createQ(q, 420);
	sendMessage(q, (void*) 420, "OQ OW, STINKYYYY, POOOOPPPYYY");
	sendMessage(q,(void*) 420, DUMMY_TEXT);

	char* result = str_encode_node(q->nodes[0]);
	free(object);
}
