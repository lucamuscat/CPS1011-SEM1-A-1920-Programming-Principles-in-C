#include "lib/functions.h"
#include "lib/functions_str.h"
#include "lib/utils.h"
#include <stdio.h>
#include <stdlib.h>

/* void test_int_lib(){ */
/* 	myint_t data = create_t(); */
/* 	int status_code = generate(data.nums, 55); */
/* 	if(status_code == OVERFLOW){ */
/* 		printf("Error"); */
/* 		return; */
/* 	} */
/* 	int_print_array(data.nums); */
/* 	shoot(&data); */
/* 	shuffle(data.nums); */
/* 	puts("====="); */
/* 	int_print_array(data.nums); */
/* 	printf("target: %d", target(&data)); */
/* 	puts("====="); */
/* 	int* sorted_array = sort(data.nums); */
/* 	int_print_array(sorted_array); */
/* 	free(sorted_array); */
/* } */

/* void test_str_lib() { */
/* 	mystr_t data; */
/* 	str_generate(&data, 2); */
/* 	str_print_array(&data); */
/* 	str_shuffle(&data); */
/* 	str_print_array(&data); */
/* 	mystr_t sorted = str_sort(&data); */
/* 	str_print_array(&sorted); */
/* } */

int main() {
	menu();
	return 0;
}
