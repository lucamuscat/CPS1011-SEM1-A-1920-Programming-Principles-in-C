#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void print_array(int* array_p){
	for(size_t i = 0; i < N; ++i){
		printf("%d\n", array_p[i]);
	}
}

int main()
{
	myint_t data = create_t();
	int status_code = generate(data.nums, 55);
	if(status_code == OVERFLOW){
		printf("Error");
		return 1;
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
    return 0;
}
