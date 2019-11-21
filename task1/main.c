#include <stdio.h>
#include <stdlib.h>
#include "lib/functions.h"
#include "lib/functions_str.h"

void print_array(int* array_p){
	for(size_t i = 0; i < N; ++i){
		printf("%d\n", array_p[i]);
	}
}

void test_int_lib(){
	myint_t data = create_t();
	int status_code = generate(data.nums, 55);
	if(status_code == OVERFLOW){
		printf("Error");
		return;
	}
	print_array(data.nums);
	shoot(&data);
	shuffle(data.nums);
	puts("=====");
	print_array(data.nums);
	printf("target: %d", target(&data));
	puts("=====");
	int* sorted_array = sort(data.nums);
	print_array(sorted_array);
	free(sorted_array);
}

int main()
{
	mystr_t data;
	str_generate(data.nums, 2);
    return 0;
}
