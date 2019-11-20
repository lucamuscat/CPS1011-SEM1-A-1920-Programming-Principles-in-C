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
