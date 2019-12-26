#include "lib/task2a/task2a_functions.h"
#include <stdio.h>
#include <stdlib.h>

void error_handler(int status, char* error_message) {
	if(status == -1){
		puts(error_message);
	}else{
		puts("Passed");
	}
}

void test_send_message(MsgQs_t* q) {
	createQ(q, 128);
	sendMessage(q,(void*) 128, "THIS IS A TEST");
	sendMessage(q,(void*) 128, "THIS IS ANOTHER TEST");
	sendMessage(q,(void*) 128, "WOOOOOWOOOOO");
	createQ(q, 205);
	sendMessage(q, NULL, "This will be sent worldwide");
	sendMessageBatch(q, "So will this ... ");
	listQs(q);
}

void test_persist_restore(MsgQs_t *q) {
	persistQ(q, 128);
	deleteQ(q, 128);
	listQs(q);
	restoreQ(q, 128);
	listQs(q);
}

int main(void) {
	MsgQs_t *q;
	// You'll get a segault if you don't initialize.
	q = initializeMsgQs();
	test_send_message(q);
	test_persist_restore(q);
}
