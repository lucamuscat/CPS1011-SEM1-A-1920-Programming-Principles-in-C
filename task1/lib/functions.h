#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "utils.h"

#define MIN_I 1
#define OVERFLOW -3
#define OVERFLOW_ERROR "Current input will cause overflow."
#define SHOT 1
#define SHOT_ERROR "Shoot function has already been called"

#define NO_TARGET -1
#define NO_TARGET_ERROR "Please call the shoot function first"
#define NOT_GENERATED -2
#define NOT_GENERATED_ERROR "Please call the generate function first"

/*
  Populates an array with a sequence of N integers, in
  ascending order , starting off integer i having a minimum value of
  1. N is defined as a constant.  This function is destructive,
  meaning that it takes a pointer to the array and overwrites values.
  @param *array: Pointer to array which is going to have values generated in it.
  @param i: First number of the generated numbers.
  @return: 1 for an overflow, 0 for no overflow.
*/
int generate(myint_t *array, int i);

/*
  Shuffles an array
  @param *array: Pointer to the array which should be shuffled.
*/
int shuffle(myint_t *array);

/*
  Sorts an array in ascending order. Selection sort is going to be used since it is the simplest and easiest to implement.
  @param *array: Pointer to array which needs to be sorted.
  @return: Returns a myint_t struct containing a sorted array. This is due to the
  fact that the question asked to return a sorted array and not to
  sort an array.
*/
myint_t sort(myint_t *array);

/*
  Zeroes out an element from the array, returns an error if an element
  has already been zeroed out. Will return a 1 if successful and a 0
  if an error has been encountered
  @param *array: Takes a myint_t struct which holds the int array and the shotgunned value.
  @return: 1 if already shot (error), 0 if not shot.
*/
int shoot(myint_t *array);


/*
  Gives the value of the shotgunned value in an array. With the
  introduction of the struct, this function becomes redundant.
  @param *array: Extracts the shotgunned value from a myint_t struct.
  @return: -1 (NO_TARGET) if no target is found and
*/
int target(myint_t *array);

#endif
