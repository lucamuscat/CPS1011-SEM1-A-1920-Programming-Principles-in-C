#include "lib/task2b/task2b_functions.h"

int main(void) {
	MsgQs_t* test = initializeMsgQs();
 	createQ(test, 110);
	createQ(test, 96);
	deleteQ(test, 96);
	// Testing for long string encoding.
	sendMessage(test,(void*) 110, "Pink Floyd", "Comfortably Numb", "Hello? (Hello, hello, hello) Is there anybody in there?  Just nod if you can hear me Is there anyone home?  Come on (Come on, come on), now I hear you're feeling down Well, I can ease your pain And get you on your feet again Relax (Relax, relax, relax) I'll need some information first Just the basic facts Can you show me where it hurts?  There is no pain, you are receding A distant ship, smoke on the horizon You are only coming through in waves Your lips move, but I can't hear what you're saying When I was a child, I had a fever My hands felt just like two balloons Now I've got that feeling once again I can't explain, you would not understand This is not how I am I have become comfortably numb I have become comfortably numb Okay (Okay, okay, okay) Just a little pinprick There'll be no more But you may feel a little sick Can you stand up? (Stand up, stand up) I do believe it's working, good That'll keep you going through the show Come on, it's time to go There is no pain, you are receding A distant ship, smoke on the horizon You are only coming through in waves Your lips move, but I can't hear what you're saying When I was a child, I caught a fleeting glimpse Out of the corner of my eye I turned to look, but it was gone I cannot put my finger on it now The child is grown, the dream is gone have become comfortably numb");
	// Testing short string encoding.
	sendMessage(test,(void*) 110, "Luca Muscat", "aaaa", "uuuuu");
	sendMessage(test,(void*) 110, "Bob Ross", "Paint", "Trees");
	// Save/Persist the queue with the ID 110.
	persistQ(test, 110);
	// Display all the nodes in the message queue.
	listQs(test->front);
	// Display and dequeue a number of messages from the specified node.
	receiveMessages(test, 110, 2);
	puts("=================");
	// Redisplay the message queue to test that the messages have
	// actually been dequeued.
	listQs(test->front);
	// Unload the message queue to prepare for the restoreQ method.
	unloadMsgQs(test);
	// Remember to reinitialize the message queue
	// otherwise you will get segfaults.
	// nobody likes segfaults.
	test = initializeMsgQs();
	// Create the node, this is a prequisite for restoreQ to work.
	createQ(test, 110);
	restoreQ(test, 110);
	// Check if the messages have been properly deserialized from the file.
	listQs(test->front);
	// Unload the message queue again to avoid memory leaks.
	unloadMsgQs(test);
	// If the progam reached here its smooth sailing.
	return 0;
}
