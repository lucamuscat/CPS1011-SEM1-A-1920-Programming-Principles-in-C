#include "lib/task2b/task2b_functions.h"

int main(void) {
	MsgQs_t* test = initializeMsgQs();
 	createQ(test, 110);
	sendMessage(test,(void*) 110, "Pink Floyd", "Comfortably Numb", "Hello? (Hello, hello, hello) Is there anybody in there?  Just nod if you can hear me Is there anyone home?  Come on (Come on, come on), now I hear you're feeling down Well, I can ease your pain And get you on your feet again Relax (Relax, relax, relax) I'll need some information first Just the basic facts Can you show me where it hurts?  There is no pain, you are receding A distant ship, smoke on the horizon You are only coming through in waves Your lips move, but I can't hear what you're saying When I was a child, I had a fever My hands felt just like two balloons Now I've got that feeling once again I can't explain, you would not understand This is not how I am I have become comfortably numb I have become comfortably numb Okay (Okay, okay, okay) Just a little pinprick There'll be no more But you may feel a little sick Can you stand up? (Stand up, stand up) I do believe it's working, good That'll keep you going through the show Come on, it's time to go There is no pain, you are receding A distant ship, smoke on the horizon You are only coming through in waves Your lips move, but I can't hear what you're saying When I was a child, I caught a fleeting glimpse Out of the corner of my eye I turned to look, but it was gone I cannot put my finger on it now The child is grown, the dream is gone have become comfortably numb");
	sendMessage(test,(void*) 110, "Luca Muscat", "aaaa", "uuuuu");
	sendMessage(test,(void*) 110, "Bob Ross", "Paint", "Trees");
	persistQ(test, 110);
	listQs(test->front);
	receiveMessages(test, 110, 2);
	puts("=================");
	listQs(test->front);
	unloadMsgQs(test);
	restoreQ(test, 110);
	listQs(test->front);
	unloadMsgQs(test);
	return 0;
}
