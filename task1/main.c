#include <stdio.h>
#include <stdlib.h>
#include "lib/functions.h"
#include "lib/functions_str.h"

void int_print_array(int* array_p){
	for(size_t i = 0; i < N; ++i){
		printf("%d\n", array_p[i]);
	}
}

void str_print_array(mystr_t* array_p){
	for(size_t i = 0; i < array_p -> size; ++i){
		puts(array_p->nums[i]);
	}
	puts("================");
}

void test_int_lib(){
	myint_t data = create_t();
	int status_code = generate(data.nums, 55);
	if(status_code == OVERFLOW){
		printf("Error");
		return;
	}
	int_print_array(data.nums);
	shoot(&data);
	shuffle(data.nums);
	puts("=====");
	int_print_array(data.nums);
	printf("target: %d", target(&data));
	puts("=====");
	int* sorted_array = sort(data.nums);
	int_print_array(sorted_array);
	free(sorted_array);
}

int main()
{
	mystr_t data;
	str_generate(&data, 2);
	str_print_array(&data);
	str_shuffle(&data);
	str_print_array(&data);
	mystr_t sorted = str_sort(&data);
	str_print_array(&sorted);
    return 0;
}
