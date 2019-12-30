int shoot(myint_t *array){
	/*
	   Check if the shoot_value is null, meaning that it hasn't
	   been shot before.
	*/
	if(array -> shoot_value == -1 && array -> nums[0] != -1){
		// Rng(R) = {x: 0 <= x <= N-1}
		int j = random(N-1);
		array -> shoot_value = array -> nums[j];
		array -> nums[j] = 0;
		return 0;
	}
	if(array->nums[0] == -1){
		puts(NOT_GENERATED_ERROR);
		return NOT_GENERATED;
	}

	puts("Shoot function has already been called");
	return SHOT;
}
