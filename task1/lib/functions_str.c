#include "functions_str.h"
#include <string.h>

const char NUMS_STR_REPR[10][STR_N] = {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten"
};

int str_generate(char array[10][STR_N], int i){
	if (i < 1)
		i = 1;
	for(size_t j = i; j < 10; ++j){
		strcpy(array[j-i], NUMS_STR_REPR[j]);
	}
	return 10 - i;
}

void str_shuffle(char array[10][STR_N]){
	char tmp[STR_N];
	int j;
}
