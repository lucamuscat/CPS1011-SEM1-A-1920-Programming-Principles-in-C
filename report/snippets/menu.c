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
