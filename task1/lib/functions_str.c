#include "functions_str.h"
#include "utils.h"
#include <string.h>

const char NUMS_STR_REPR[11][STR_N] = {
	"zero",
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
void str_generate(mystr_t* array, int i){
	strcpy(array -> shoot_value, EMPTY);
	if (i < 1)
		i = 1;
	for(size_t j = i; j < 11; ++j){
		strcpy(array -> nums[j-i], NUMS_STR_REPR[j]);
	}
	array -> size = 10 - i + 1;
}

void str_shuffle(char array[10][STR_N]){
/*
  Same philosophy as shuffle() in functions.c but uses strcpy to swap
  strings around.
*/
void str_shuffle(mystr_t* array){
	char tmp[STR_N];
	int j;
	for (size_t i = 0; i < array->size; ++i) {
		j = random(i);
		strcpy(tmp, array -> nums[j]);
		strcpy(array -> nums[j], array -> nums[i]);
		strcpy(array -> nums[i], tmp);
	}
}

/*
  Has to take a mystr_t ptr as an arguement so that the size of the
  array is known since an array can be partially filled
*/

int str_shoot(mystr_t *array){
	if(strcmp(array -> shoot_value, EMPTY) == 0){
		int rand = random(array -> size);
		strcpy(array -> shoot_value, array -> nums[rand]);
		strcpy(array -> nums[rand], "zero");

		return 0;
	}
	return SHOT;
}
}
