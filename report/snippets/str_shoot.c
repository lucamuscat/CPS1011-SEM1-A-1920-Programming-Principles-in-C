int str_shoot(mystr_t *array){
	if(strcmp(array -> shoot_value, EMPTY) == 0){
		int rand = random(array -> size);
		strcpy(array -> shoot_value, array -> nums[rand]);
		strcpy(array -> nums[rand], "zero");

		return 0;
	}

	if(strcmp(array->nums[0], EMPTY) == 0){
		return NOT_GENERATED;
	}
	return SHOT;
}
