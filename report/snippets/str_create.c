mystr_t str_create_t() {
	mystr_t temp;
	strcpy(temp.shoot_value, EMPTY);
	strcpy(temp.nums[0], EMPTY);
	temp.size = 0;
	return temp;
}
