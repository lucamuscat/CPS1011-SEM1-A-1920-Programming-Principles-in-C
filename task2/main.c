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

    /* q = initializeMsgQs(); */
	/* restoreQ(q, 69); */
	/* listQs(q); */
	/* receiveMessages(q, 69, 4); */
	/* listQs(q); */
	/* free(q); */
}
