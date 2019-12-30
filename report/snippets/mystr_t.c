
/*
  Since the string representations of integers are limited from 1 to
  10, this means that the memory allocated to mystr_t is dynamic
*/
typedef struct mystr_t{
	char nums[10][STR_N];
	char shoot_value[STR_N];
	size_t size;
} mystr_t;
