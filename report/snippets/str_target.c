// Extract the shoot_value from the mystr_t var.
char* str_target(mystr_t *array){
	if(strcmp(array->shoot_value, EMPTY) == 0)
		return "error";
	return array->shoot_value;
}
