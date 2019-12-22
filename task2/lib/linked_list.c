#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include "task2_utils.h"

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

void unloadMsgQs(MsgQs_t *q) {
	nodeMsg_t* node = q->front;
	free_node(node);
}

void listQs(nodeMsg_t *front) {
	if(front != NULL){
		printf("ID: %d", front->ID);
		listItems(front->front);
		listQs(front->next);
	}
	listQs(front);
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
