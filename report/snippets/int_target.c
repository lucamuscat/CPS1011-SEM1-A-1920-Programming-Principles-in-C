int target(myint_t* array){
	if(array->nums[0] == -1){
		puts(NOT_GENERATED_ERROR);
		return NOT_GENERATED;
	}

	if(!array -> shoot_value){
		puts("Please shoot first.");
		return NO_TARGET;
	}
	return array -> shoot_value;
}
