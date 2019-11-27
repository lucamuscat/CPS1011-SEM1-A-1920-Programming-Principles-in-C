#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "functions.h"
#include "utils.h"

int generate(myint_t *array, int i){
  if(i < 1)
		i = 1;
	/*
	   Check for an overflow. Since checking for an overflow once it
	   happened doesn't work out so well, we check if i is smaller
	   than INT_MAX - N. If it isn't, that means that the int will
	   overflow and wrap around to a negative number. Rather than
	   dealing with
	*/
	if(i < INT_MAX - N){
		for(size_t j = i; j < i + N; ++j){
			array->nums[j - i] = j;
		}
		return 0;
	}
	printf("Overflow detected");
	return OVERFLOW;
}

/*
  Using Fisher-Yates shuffle algorithm
  https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle

  Code taken from
  https://stackoverflow.com/questions/42321370/fisher-yates-shuffling-algorithm-in-c
  - Tectrendz
*/
int shuffle(myint_t *array){
	int tmp, j;
	if(array->nums[0] == -1){
		puts(NOT_GENERATED_ERROR);
		return NOT_GENERATED;
	}
	for(size_t i = N-1; i > 0; --i){
		j = random(i);
		tmp = array->nums[j];
		array -> nums[j] = array -> nums[i];
		array -> nums[i] = tmp;
	}
}

int shoot(myint_t *array){
	/*
	   Check if the shoot_value is null, meaning that it hasn't
	   been shot before.
	*/
	if(array -> shoot_value == -1 && array -> nums[0] != -1){
		// Rng(R) = {x: 0 <= x <= N-1}
		int j = random(N-1);
		array -> shoot_value = array -> nums[j];
		array -> nums[j] = 0;
		return 0;
	}
	if(array->nums[0] == -1){
		puts(NOT_GENERATED_ERROR);
		return NOT_GENERATED;
	}

	puts("Shoot function has already been called");
	return SHOT;
}

int target(myint_t* array){
	if(array->nums[0] == -1){
		puts(NOT_GENERATED_ERROR);
		return NOT_GENERATED;
	}

	if(!array -> shoot_value){
		puts("Please shoot first.");
		return NO_TARGET;
	}
	return array -> shoot_value;
}

myint_t sort(myint_t* array){
	/*
	  Allocate the N * size of int in bytes.  Then, return the pointer
	  to the allocated contiguous memory.  and assign it to pointer p.
	*/

	/*
	  Dont forget to free the returned value at the end to avoid
	  mem leaks.
	*/

	myint_t p = *array;

	size_t min_index;

	for(size_t i = 0; i < N - 1; ++i){
		min_index = i;
		for(size_t j = i + 1; j < N; ++j){
			if(p.nums[j] < p.nums[min_index]){
				min_index = j;
			}
		}
		int temp = p.nums[i];
		p.nums[i] = p.nums[min_index];
		p.nums[min_index] = temp;
	}
	return p;
}
