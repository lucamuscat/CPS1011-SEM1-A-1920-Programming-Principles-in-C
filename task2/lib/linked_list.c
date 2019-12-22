#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#define FULL_QUEUE_ERROR -1
#define EMPTY_ERROR -2

#define MESSAGE_LENGTH 256
#define LIMIT 25

MsgQs_t* initializeMsgQs() {
	MsgQs_t *q = (MsgQs_t*) malloc(sizeof(MsgQs_t));
	q -> size = 0;
	q -> front = NULL;
	q -> rear = NULL;
	return q;
}

// Returns EMPTY_ERROR when empty and 1 when not empty.
int is_empty(MsgQ_t *queue) {
	return queue->size == 0;
}

int enqueue(MsgQ_t *container, char message[MESSAGE_LENGTH]) {
int createQ(MsgQs_t *q, int identifier) {
	if(contains_id(q->front, identifier))
		return -1;
	nodeMsg_t *tmp;
	tmp = malloc(sizeof(nodeMsg_t));
	tmp -> front = malloc(sizeof(Item));
	tmp->ID = identifier;
	if(is_empty(q)){
		q -> front = tmp;
		q -> rear = tmp;
	} else{
		q -> rear -> next = tmp;
		q -> rear = tmp;
		//
	}
	q->size++;
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
void listQs(nodeMsg_t *front) {
	if(front != NULL){
		printf("ID: %d", front->ID);
		listItems(front->front);
		listQs(front->next);
	}
	listQs(front);
	return;
}

}
