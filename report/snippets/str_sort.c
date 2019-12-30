/*
  Use the predefined 2d char array to compare values this is
  convenient as each index maps to their respective number.
*/
int* str_to_int(mystr_t *array){
	int *temp = malloc(sizeof(int) * array->size);
	for(size_t i = 0; i < array -> size; ++i){
		temp[i] = -1;
		for(size_t j = 0; j < 11; ++j){
			if(strcmp(array->nums[i], NUMS_STR_REPR[j]) == 0){
				temp[i] = j;
				break;
			}
		}
	}
	return temp;
}

// Using selection sort.
mystr_t str_sort(mystr_t *array){
	mystr_t temp = *array;
	size_t min_index;
	int *int_repr = str_to_int(array);
	for(size_t i = 0; i < array->size; ++i){
		min_index = i;
		for(size_t j = i +1; j < array->size; ++j){
			if(int_repr[j] < int_repr[min_index])
				min_index = j;
		}
		int_swap(&int_repr[i], &int_repr[min_index]);
		/*
		   temp.nums is a 2d array so the address operator won't need
		   to be used
		*/
		str_swap(temp.nums[i], temp.nums[min_index]);
	}
	return temp;
}
