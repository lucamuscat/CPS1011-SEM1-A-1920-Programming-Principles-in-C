#include "lib/task2b_functions.h"
#define COPY_PASTA "I'm sick and tired of seeing pictures of babies on my favorite subreddits.I follow a subreddit for a book series I recently finished and here on the front page is some dudes baby because he named her after a character in the book.I follow a football subreddit and here is some dudes baby in a jersey.I follow a gaming subreddit and here is a picture of some dude holding his baby and playing the game.Gtfo of here."
int main(void) {
	MsgQs_t* test = initializeMsgQs();
 	createQ(test, 420);
	/* sendMessage(test,(void*) 420, "Snoop Dogg", "Ganja my dude", "AAAAAAAAA WEEEEEEDDDD"); */
	/* sendMessage(test,(void*) 420, "Luca Muscat", "aaaa", "uuuuu"); */
	/* sendMessage(test,(void*) 420, "Bob Ross", "Paint", "Trees"); */
	/* sendMessage(test,(void*) 420, "Boss Baby", "Gugu gaga", COPY_PASTA); */
	/* persistQ(test, 420); */
	/* listQs(test->front); */
	/* receiveMessages(test, 420, 2); */
	/* puts("================="); */
	/* listQs(test->front); */
	/* unloadMsgQs(test); */
	restoreQ(test, 420);
	listQs(test->front);
	return 0;
}
