#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define N 25
#define MIN_I 1
#define OVERFLOW 1
#define SHOT 1
#define NO_TARGET -1


/*
  Creating a structure which holds an array of ints, a boolean to
  check if its shotgunned (to prevent nulls) and the shotgunned value.
*/

typedef struct myint_t{
	int nums[N];
	int shoot_value;
} myint_t;

/*
   This helper function was used to help give shoot_value a
   pseudo-null value when initialized.
   @return: myint_t with shoot_value declared to -1
*/
myint_t create_t();

/*
  Generates a random number from a new seed every time.
  @return: Return a pseudo-random number.
*/
int random();

/*
  Populates an array with a sequence of N integers, in
  ascending order , starting off integer i having a minimum value of
  1. N is defined as a constant.  This function is destructive,
  meaning that it takes a pointer to the array and overwrites values.
  @param *array: Pointer to array which is going to have values generated in it.
  @param i: First number of the generated numbers.
  @return: 1 for an overflow, 0 for no overflow.
*/
int generate(int *array, int i);

/*
  Shuffles an array
  @param *array: Pointer to the array which should be shuffled.
*/
void shuffle(int *array);

/*
  Sorts an array in ascending order. Selection sort is going to be used since it is the simplest and easiest to implement.
  @param *array: Pointer to array which needs to be sorted.
  @return: Returns a pointer to a sorted array. This is due to the
  fact that the question asked to return a sorted array and not to
  sort an array.
*/
int* sort(int *array);

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
*/
int target(myint_t *array);

#endif
