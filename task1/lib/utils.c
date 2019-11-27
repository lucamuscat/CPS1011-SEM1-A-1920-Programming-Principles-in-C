#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "functions.h"
#include "functions_str.h"

myint_t create_t(){
	myint_t temp;
	for(size_t i = 0; i < N; ++i){
		temp.nums[i] = -1;
	}
	temp.shoot_value = -1;
	return temp;
}

void int_print_array(myint_t* array_p){
	for(size_t i = 0; i < N; ++i){
		printf("%d\n", array_p->nums[i]);
	}
}

void str_print_array(mystr_t* array_p){
	for(size_t i = 0; i < array_p -> size; ++i){
		puts(array_p->nums[i]);
	}
	puts("================");
}

int random(int range){
	/*
	  This way a completely random seed will be used for every random
	  number
	*/
	srand(time(NULL));
	/*
	  rand() % i generates random numbers from 1 to i-1.
	  Hence the +1.
	*/
	return rand() % (range + 1);
}

void menu_print() {
	puts("==================");
	puts("Welcome to the Problem Solving Assignment\nPlease select an option.");
	puts("1. Generate \t 6. String Generate");
	puts("2. Shuffle \t 7. String Shuffle");
	puts("3. Sort \t 8. String Sort");
	puts("4. Shoot \t 9. String Shoot");
	puts("5. Target \t 10. String Target");
	puts("Please insert a character to terminate");
	puts("==================");
}

void int_input(int *input) {
	int ret_status;
	do{
		ret_status = scanf("%d", input);
	}while(ret_status != 1);
}

void error_handling(int function_status) {
	switch (function_status) {
	case NOT_GENERATED:
		puts(NOT_GENERATED_ERROR);
		break;
	case NO_TARGET:
		puts(NO_TARGET_ERROR);
		break;
	case SHOT:
		puts(SHOT_ERROR);
		break;
	case OVERFLOW:
		puts(OVERFLOW_ERROR);
		break;
	}
}

void menu() {
	int status;
	int option;
	myint_t data_int = create_t();
	mystr_t data_str = str_create_t();
	int function_status = -1;
	do{
		menu_print();
		status = scanf("%d", &option);
		puts("=============");
		int input;
		switch(option){
		case 1:
			// Generate
			puts("Please insert the number you want to start from.");
			int_input(&input);
			function_status = generate(&data_int, input);
			break;
		case 2:
			// Shuffle
			function_status = shuffle(&data_int);
			if(function_status != NOT_GENERATED)
				int_print_array(&data_int);
			break;
		case 3:
			// Sort
			// Technically the sort function still returns a new array.
			data_int = sort(&data_int);
			int_print_array(&data_int);
			break;
	    case 4:
			function_status = shoot(&data_int);
			break;
		case 5:
			function_status = target(&data_int);
			if(function_status != NO_TARGET || function_status != NOT_GENERATED){
				printf("%d", function_status);
			}
			break;
		case 6:
			// str generate
			puts("Please insert starting number (between 1 and 10)");
			do{
				int_input(&input);
			}while(input < 1 || input > 10);
			str_generate(&data_str, input);
			str_print_array(&data_str);
			break;
		case 7:
			// str shuffle
			function_status = str_shuffle(&data_str);
			str_print_array(&data_str);
			break;
		case 8:
			// str_sort
			if(strcmp(data_str.nums[0], EMPTY) == 0){
				puts(NOT_GENERATED_ERROR);
			}else {
				data_str = str_sort(&data_str);
				str_print_array(&data_str);
			}
			break;
		case 9:
			function_status = str_shoot(&data_str);
			if(function_status != SHOT)
				puts(data_str.shoot_value);
			break;
		case 10:
			puts(str_target(&data_str));
		default:
			error_handling(function_status);
			break;
		}
	}while(status == 1); // Stop if a character is encountered.

}
