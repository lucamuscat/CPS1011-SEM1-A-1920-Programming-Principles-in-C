#include <stdlib.h>
#include <time.h>
#include "utils.h"


myint_t create_t(){
	myint_t temp;
	temp.shoot_value = -1;
	return temp;
}

int random(int range){
	/*
	  This way a completely random seed will be used for every random
	  number
	*/
	srand(time(NULL));
	/*
	  rand() % i generates random numbers from 1 to i-1.
	  Hence the +1.
	*/
	return rand() % (range + 1);
}
