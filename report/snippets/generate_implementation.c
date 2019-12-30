int generate(myint_t *array, int i){
  if(i < 1)
	i = 1;
	/*
	   Check for an overflow. Since checking for an overflow once it
	   happened doesn't work out so well, we check if i is smaller
	   than INT_MAX - N. If it isn't, that means that the int will
	   overflow and wrap around to a negative number. Rather than
	   dealing with
	*/
	if(i < INT_MAX - N){
		for(size_t j = i; j < i + N; ++j){
			array->nums[j - i] = j;
		}
		return 0;
	}
	printf("Overflow detected");
	return OVERFLOW;
}
