#ifndef FUNCTIONS_STR_H
#define FUNCTIONS_STR_H

// Largest number in string representation has a length of 5, bit is left as extra for the null byte
#define STR_N 6
#define MIN_I 1

#include <stdlib.h>
#include "functions.h"

char NUMS_STR_REPR[11][STR_N];

/*
  Creating a structure which holds an array of ints, a boolean to
  check if its shotgunned (to prevent nulls) and the shotgunned value.
*/

/*
  Since the string representations of integers are limited from 1 to
  10, this means that the memory allocated to mystr_t is dynamic
*/
typedef struct mystr_t{
	char nums[10][STR_N];
	char shoot_value[STR_N];
	size_t size;
} mystr_t;

/*
   This helper function was used to help give shoot_value a
   pseudo-null value when initialized.
   @return: myint_t with shoot_value declared to -1
*/
mystr_t str_create_t();

/*
  Populates an array with the string representation of the numbers from i
  to 10 (minimum of i being 1). The data won't be stored as a 2D array.
  Everything will be placed in a 1D array, having each element split by a string
  terminator byte. This allows for the data to be tokenized.
  @param *array: Pointer to array which is going to have values generated in it.
  @param i: First number of the generated numbers.
*/
void str_generate(mystr_t *array, int i);

/*
  Shuffles an array
  @param *array: Pointer to the array which should be shuffled.
  @return: Returns a NOT_GENERATED error code if not generated.
*/
int str_shuffle(mystr_t *array);

/*
  @param *array: Pointer to mystr_t struct which needs to be sorted.
  @return: Returns a pointer to a sorted array. This is due to the
  fact that the question asked to return a sorted array and not to
  sort an array.
*/
mystr_t str_sort(mystr_t* array);

/*
  Zeroes out an element from the array, returns an error if an element
  has already been zeroed out. Will return a 1 if successful and a 0
  if an error has been encountered
  @param *array: Takes a myint_t struct which holds the int array and the shotgunned value.
  @return: 1 if already shot (error), 0 if not shot.
*/
int str_shoot(mystr_t *array);


/*
  Gives the value of the shotgunned value in an array. With the
  introduction of the struct, this function becomes redundant.
  @param *array: Extracts the shotgunned value from a myint_t struct.
*/
char* str_target(mystr_t *array);

int* str_to_int(mystr_t *array);

#endif
