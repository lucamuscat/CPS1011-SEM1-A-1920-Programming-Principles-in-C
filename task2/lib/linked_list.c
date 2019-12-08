#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FULL_QUEUE_ERROR -1
#define EMPTY_ERROR -2

#define MESSAGE_LENGTH 256
#define LIMIT 25

/*
  First things first, create a queue
*/

/*
  MsgQ_t will first be implemented as an array for task 2a
  it will then be implemented as a linked list for task 2
*/

struct nodeMsg_t {
	char message[256];
	struct nodeMsg_t *next;
};
typedef struct nodeMsg_t nodeMsg_t;

typedef struct MsgQ_t {
	size_t size;
	nodeMsg_t *front;
	nodeMsg_t *rear;
} MsgQ_t;

void init(MsgQ_t *queue) {
	queue -> size = 0;
	queue -> front = NULL;
	queue -> rear = NULL;
}

// Returns EMPTY_ERROR when empty and 1 when not empty.
int is_empty(MsgQ_t *queue) {
	return queue->size == 0;
}

int enqueue(MsgQ_t *container, char message[MESSAGE_LENGTH]) {
	nodeMsg_t *tmp;
	tmp = malloc(sizeof(nodeMsg_t));
	strcpy(tmp -> message, message);
	if(is_empty(container)){
		container -> front = tmp;
		container -> rear = tmp;
	} else{
		container -> rear -> next = tmp;
		container -> rear = tmp;
		//
	}
	container->size++;
}

int dequeue(MsgQ_t *container, char * message_container){
	nodeMsg_t *tmp;
	strcpy(message_container, container->front->message);
	tmp = container -> front;
	container -> front = container -> front -> next;
	container->size--;
	free(tmp);
	return 1;
}

void display(nodeMsg_t *front) {
	if(front != NULL){
		puts(front -> message);
		display(front->next);
	}
}

void test(void) {
	MsgQ_t *q;
	q = malloc(sizeof(MsgQ_t));
	init(q);
	enqueue(q, "Luca");
	enqueue(q, "Bob");
	enqueue(q, "John Mayor");
	enqueue(q, "Ross");
	display(q->front);
}
