#include "lib/task2b_functions.h"
int main(void) {
	MsgQs_t* test = initializeMsgQs();
	createQ(test, 420);
	sendMessage(test,(void*) 420, "Snoop Dogg", "Ganja my dude", "AAAAAAAAA WEEEEEEDDDD");
	sendMessage(test,(void*) 420, "Luca Muscat", "aaaa", "uuuuu");
	sendMessage(test,(void*) 420, "Bob Ross", "Paint", "Trees");
	listQs(test->front);
	receiveMessages(test, 420, 2);
	puts("=================");
	listQs(test->front);
	unloadMsgQs(test);
	return 0;
}
