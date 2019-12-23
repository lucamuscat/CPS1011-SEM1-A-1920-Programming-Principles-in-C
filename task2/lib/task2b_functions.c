#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task2b_functions.h"
#include "task2b_utils.h"

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

// Enqueue a MsgQs_t variable.
int createQ(MsgQs_t *q, int identifier) {
	if(contains_id(q->front, identifier))
		return -1;
	nodeMsg_t *tmp;
	tmp = malloc(sizeof(nodeMsg_t));
	tmp->next = NULL;
	tmp->ID = identifier;
	tmp->size = 0;
	if(is_empty(q)){
		q -> front = tmp;
		q -> rear = tmp;
	} else{
		q -> rear -> next = tmp;
		q -> rear = tmp;
	}
	q->size++;
	return 1;
}

void unloadMsgQs(MsgQs_t *q) {
	nodeMsg_t* node = q->front;
	free_node(node);
}

void listQs(nodeMsg_t *front) {

	if(front->size == 0){
		puts("This is empty :/");
	} else {
		printf("\nID: %d", front->ID);
		listItems(front->front);
	}
	if(front->next != NULL){
		return listQs(front->next);
	}
	return;
}

int deleteQ(MsgQs_t* q, int identifier){
	if(q->front->ID == identifier){
		nodeMsg_t* temp = q->front;
		free_item(temp->front);
		q->front = temp->next;
		return 1;
	}
	return removeQ(q->front, identifier);
}

// returns an error if queue id doesn't exist
void sendMessageBatch(MsgQs_t *q, char* sender, char* subject, char* content) {
	size_t size = q->size;
	/* nodeMsg_t* front = q->front; */
	/* while(size > 0){ */
	/* 	enqueue_nodeMsg_t(front, sender, subject, content); */
	/* 	front = front->next; */
	/* 	size--; */
	/* } */
	batch_populate_node(q->front, sender, subject, content);
}
