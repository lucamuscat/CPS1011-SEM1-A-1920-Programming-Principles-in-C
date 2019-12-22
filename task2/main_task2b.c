#include "lib/task2b_functions.h"
int main(void) {
	MsgQs_t* test = initializeMsgQs();
	createQ(test, 420);
	createQ(test, 69);
	sendMessageBatch(test, "Luca Muscat", "Yo, Angelo", "Sorry for turning you into a rock :/");
	listQs(test->front);
	unloadMsgQs(test);
	return 0;
}
