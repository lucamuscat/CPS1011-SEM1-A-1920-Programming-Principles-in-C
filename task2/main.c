#include "lib/basic_queue.h"
#include <stdio.h>
#include <stdlib.h>

void error_handler(int status, char* error_message) {
	if(status == -1){
		puts(error_message);
	}else{
		puts("Passed");
	}
}

int main(void) {
	MsgQs_t *q;
	q = initializeMsgQs();
	error_handler(createQ(q, 69), "ENQUEUE ERROR");
	error_handler(createQ(q, 420), "ENQUEUE ERROR");
	error_handler(createQ(q, 42069), "ENQUEUE ERROR");
	error_handler(deleteQ(q, 420), "DOESN'T EXIST");
	sendMessageBatch(q, "Whats poppin jimbo");
	listQs(q);
	sendMessage(q, NULL, "Ayye this is a null");
	listQs(q);
	sendMessage(q, 69, "Sixty nine ninty nine");
	listQs(q);
	purgeQs(q, 69);
	listQs(q);
	purgeQs(q, NULL);
	listQs(q);
	free(q);
}
