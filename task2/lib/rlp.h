#ifndef RLP_H
#define RLP_H
#include <stdio.h>

void rlp_encode_str(char *string, char *buffer);
size_t rlp_strlen(char *string);
char* rlp_encode_list(size_t length);
char* str_encode_length(size_t length);
size_t byte_len(size_t number);
#endif
