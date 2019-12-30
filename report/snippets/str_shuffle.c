/*
  Same philosophy as shuffle() in functions.c but uses strcpy to swap
  strings around.
*/
int str_shuffle(mystr_t* array){
	char tmp[STR_N];
	int j;

	if(array->size == 0){
		return NOT_GENERATED;
	}

	for (size_t i = 0; i < array->size; ++i) {
		j = random(i);
		strcpy(tmp, array -> nums[j]);
		strcpy(array -> nums[j], array -> nums[i]);
		strcpy(array -> nums[i], tmp);
	}
}
