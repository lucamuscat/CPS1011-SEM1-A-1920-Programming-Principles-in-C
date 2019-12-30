
myint_t sort(myint_t* array){
	/*
	  Allocate the N * size of int in bytes.  Then, return the pointer
	  to the allocated contiguous memory.  and assign it to pointer p.
	*/

	/*
	  Dont forget to free the returned value at the end to avoid
	  mem leaks.
	*/

	myint_t p = *array;

	size_t min_index;

	for(size_t i = 0; i < N - 1; ++i){
		min_index = i;
		for(size_t j = i + 1; j < N; ++j){
			if(p.nums[j] < p.nums[min_index]){
				min_index = j;
			}
		}
		int temp = p.nums[i];
		p.nums[i] = p.nums[min_index];
		p.nums[min_index] = temp;
	}
	return p;
}
