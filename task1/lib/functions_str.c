#include "functions_str.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>

char NUMS_STR_REPR[11][STR_N] = {
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

mystr_t str_create_t() {
	mystr_t temp;
	strcpy(temp.shoot_value, EMPTY);
	strcpy(temp.nums[0], EMPTY);
	temp.size = 0;
	return temp;
}

void str_generate(mystr_t* array, int i){
	strcpy(array -> shoot_value, EMPTY);
	if (i < 1)
		i = 1;
	for(size_t j = i; j < 11; ++j){
		strcpy(array -> nums[j-i], NUMS_STR_REPR[j]);
	}
	array -> size = 10 - i + 1;
}

/*
  Same philosophy as shuffle() in functions.c but uses strcpy to swap
  strings around.
*/
int str_shuffle(mystr_t* array){
	char tmp[STR_N];
	int j;

	if(array->size == 0){
		return NOT_GENERATED;
	}

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

	if(strcmp(array->nums[0], EMPTY) == 0){
		return NOT_GENERATED;
	}
	return SHOT;
}
// Extract the shoot_value from the mystr_t var.
char* str_target(mystr_t *array){
	if(strcmp(array->shoot_value, EMPTY) == 0)
		return "error";
	return array->shoot_value;
}
void int_swap(int* a, int* b){
	//Swap ints
	int temp = *a;
	*a = *b;
	*b = temp;
}
void str_swap(char* a, char* b){
	char temp[STR_N];
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}

/*
  Use the predefined 2d char array to compare values this is
  convenient as each index maps to their respective number.
*/
int* str_to_int(mystr_t *array){
	int *temp = malloc(sizeof(int) * array->size);
	for(size_t i = 0; i < array -> size; ++i){
		temp[i] = -1;
		for(size_t j = 0; j < 11; ++j){
			if(strcmp(array->nums[i], NUMS_STR_REPR[j]) == 0){
				temp[i] = j;
				break;
			}
		}
	}
	return temp;
}

// Using selection sort.
mystr_t str_sort(mystr_t *array){
	mystr_t temp = *array;
	size_t min_index;
	int *int_repr = str_to_int(array);
	for(size_t i = 0; i < array->size; ++i){
		min_index = i;
		for(size_t j = i +1; j < array->size; ++j){
			if(int_repr[j] < int_repr[min_index])
				min_index = j;
		}
		int_swap(&int_repr[i], &int_repr[min_index]);
		/*
		   temp.nums is a 2d array so the address operator won't need
		   to be used
		*/
		str_swap(temp.nums[i], temp.nums[min_index]);
	}
	return temp;
}
