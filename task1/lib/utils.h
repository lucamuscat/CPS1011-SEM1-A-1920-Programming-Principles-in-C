/*
  This file was created to seperate helper functions from functions
  that are important for the assignment. This helps with the
  readability and prioritization of code
*/

#ifndef UTILS_H
#define UTILS_H

#define N 25

/*
  Creating a structure which holds an array of ints, a boolean to
  check if its shotgunned (to prevent nulls) and the shotgunned value.
*/

typedef struct myint_t{
	int nums[N];
	int shoot_value;
} myint_t;

/*
  Generates a random number from a new seed every time.
  @return: Return a pseudo-random number.
*/
int random(int range);

/*
   This helper function was used to help give shoot_value a
   pseudo-null value when initialized.
   @return: myint_t with shoot_value declared to -1
*/
myint_t create_t();

#endif
