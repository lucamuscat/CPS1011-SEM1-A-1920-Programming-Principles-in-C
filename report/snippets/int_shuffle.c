
/*
  Using Fisher-Yates shuffle algorithm
  https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle

  Code taken from
  https://stackoverflow.com/questions/42321370/fisher-yates-shuffling-algorithm-in-c
  - Tectrendz
*/
int shuffle(myint_t *array){
	int tmp, j;
	if(array->nums[0] == -1){
		puts(NOT_GENERATED_ERROR);
		return NOT_GENERATED;
	}
	for(size_t i = N-1; i > 0; --i){
		j = random(i);
		tmp = array->nums[j];
		array -> nums[j] = array -> nums[i];
		array -> nums[i] = tmp;
	}
}
